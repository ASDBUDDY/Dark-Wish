#include <pokeagb/pokeagb.h>
#include "../battle_slide_in_data/battle_obj_sliding.h"
#include "../battle_data/pkmn_bank.h"
#include "../battle_data/pkmn_bank_stats.h"
#include "../battle_data/battle_state.h"
#include "../battle_events/battle_events.h"
#include "../battle_text/battle_textbox_gfx.h"
#include "../hpboxes/hpbox_positional_data.h"

extern void battle_loop(void);
extern void C2SyncAll(void);
extern void VblankMergeTextBox(void);
extern const struct BgConfig configBattleReturn[4];
extern void pick_and_load_battle_bgs_no_entry(const void* txtbox);
extern void CpuFastSet(void*, void*, u32);
extern void create_sprites_battle_mons_wild(void);
extern void BankSelectOption(u8 bank);
extern void HandlersClear(void);
extern void ResetAndHideBGs(void);
extern void validate_player_selected_move(void);
extern void free_unused_objs(void);
extern bool bank_trapped(u8 bank);
extern void AnimationMain(void);
extern struct action* QueueMessage(u16 move, u8 bank, enum battle_string_ids id, u16 effect);
extern struct TextboxTemplate BattleTextBoxes[];
extern void NullBattleSpriteTracker(void);

void return_to_battle()
{
    switch(gMain.state) {
        case 0:
            if (!gPaletteFade.active) {
                u32 set = 0;
                CpuFastSet((void*)&set, (void*)ADDR_VRAM, CPUModeFS(0x10000, CPUFSSET));
                SetVBlankCallback((MainCallback)VblankMergeTextBox);
                SetMainCallback2((MainCallback)C2SyncAll);
                bg_vram_setup(0, (struct BgConfig *)&configBattleReturn, 4);
                rbox_init_from_templates((struct TextboxTemplate*)&BattleTextBoxes[0]);
                if (gBattleMaster->switch_main.reason == ViewPokemon)
                    pick_and_load_battle_bgs_no_entry(battle_textbox_action_selectMap);
                else
                    pick_and_load_battle_bgs_no_entry(battle_textboxMap);
                gMain.state++;
            }
            break;
        case 1:
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, 0x0000);
            // show bgs for background and entry image
            ShowBg(3);
            ShowBg(0);
            // show oams
            for (u8 i = 0; i < BANK_MAX; i++) {
                // show pokemon OAMs
                if (gPkmnBank[i]->objid < 0x3F && !HAS_VOLATILE(i, VOLATILE_SEMI_INVULNERABLE)) {
                    OBJID_SHOW(gPkmnBank[i]->objid);
                    gSprites[gPkmnBank[i]->objid].final_oam.h_flip = false;
                    gSprites[gPkmnBank[i]->objid].final_oam.v_flip = false;
                }
                // show HP box OAMs
                for (u8 j = 0; j < 4; j++) {
                    if (gPkmnBank[i]->objid_hpbox[j] < 0x3F)
                        OBJID_SHOW(gPkmnBank[i]->objid_hpbox[j]);
                }
            }
            gMain.state++;
            break;
        case 2:
            if (gPaletteFade.active) return;
            gMain.state++;
        case 3:
            switch (gBattleMaster->switch_main.reason) {
                case ViewPokemon:
                    BankSelectOption(gBattleMaster->option_selecting_bank);
                    return;
                case NormalSwitch:
                    // is the Pokemon trapped ?
                    if (bank_trapped(gBattleMaster->option_selecting_bank)) {
                        if (ACTION_HEAD == NULL) {
                            // build actions
                            ACTION_HEAD = add_action(0xFF, 0xFF, ActionHighPriority, EventEndAction);
                            CURRENT_ACTION = ACTION_HEAD;
                            QueueMessage(MOVE_NONE, gBattleMaster->option_selecting_bank, STRING_TRAPPED, 0);
                            SetMainCallback(battle_loop);
                            return;
                        } else {
                            QueueMessage(MOVE_NONE, gBattleMaster->option_selecting_bank, STRING_TRAPPED, 0);
                            BankSelectOption(gBattleMaster->option_selecting_bank);
                        }
                        return;
                    }
                    gPkmnBank[PLAYER_SINGLES_BANK]->battleData.isSwitching = true;
                    gPkmnBank[PLAYER_SINGLES_BANK]->this_pkmn = &party_player[gBattleMaster->switch_main.position];
                    gMain.state = 0;
                    validate_player_selected_move();
                    end_action(CURRENT_ACTION);
                    SetMainCallback(battle_loop);
                    return;
                case ForcedSwitch:
                    gPkmnBank[PLAYER_SINGLES_BANK]->this_pkmn = &party_player[gBattleMaster->switch_main.position];
                    gMain.state = 0;
                    gPkmnBank[PLAYER_SINGLES_BANK]->battleData.isSwitching = false;
                    SetMainCallback(battle_loop);
                    return;
                case PokemonFainted:
                    gPkmnBank[PLAYER_SINGLES_BANK]->this_pkmn = &party_player[gBattleMaster->switch_main.position];
                    gMain.state = 0;
                    CURRENT_ACTION->event_state++;
                    SetMainCallback(battle_loop);
                    return;
            };
            dprintf("INVALID SWITCH REASON WAS GIVEN\n");
            gMain.state++;
            break;
        case 4:
            break;
    };

}

extern void ResetPals(void);
extern u8 spawn_hpbox_opponent(u16 tag, s16 x, s16 y, u8 bank);
extern u8 spawn_hpbox_player(u16 tag, s16 x, s16 y, u8 bank);
void ReturnToBattleFromBag()
{
    switch (gMain.state) {
        case 0:
            // display
            lcd_io_set(0x4C, 0);
            REG_WININ = WININ_BUILD(WIN_BG0 | WIN_BG1 | WIN_BG2 | WIN_BG3 | WIN_OBJ | WIN_BLD,
            WIN_BG0 | WIN_BG1 | WIN_BG2 | WIN_BG3 | WIN_OBJ | WIN_BLD);
            rboxes_free();

            // callbacks
            HandlersClear();
            SetMainCallback(ReturnToBattleFromBag);
            SetMainCallback2((MainCallback)C2SyncAll);
            SetVBlankCallback((MainCallback)VblankMergeTextBox);

            // BG stuff
            u32 set = 0;
            CpuFastSet((void*)&set, (void*)ADDR_VRAM, CPUModeFS(0x10000, CPUFSSET));
            ResetPals();
            gpu_tile_bg_drop_all_sets(0);
            bg_vram_setup(0, (struct BgConfig *)&configBattleReturn, 4);
            // BGs
            dprintf("var 0x800E is %d\n", var_800E);
            if (var_800E == 0) {
                pick_and_load_battle_bgs_no_entry(battle_textbox_action_selectMap);
            } else {
                pick_and_load_battle_bgs_no_entry(battle_textboxMap);
            }
            HideBg(0);
            HideBg(1);
            HideBg(2);
            HideBg(3);
            gMain.state++;
            break;
        case 1:
            {
            // objs
            for (u8 i = 0; i < 0x3F; i++) {
                obj_free(&gSprites[i]);
            }
            ResetSpriteData();
            gpu_tile_obj_tags_reset();
            // need to redraw gSprites
            create_sprites_battle_mons_wild();
            gSprites[gPkmnBank[OPPONENT_SINGLES_BANK]->objid].pos1.x = 178;
            for (u8 i = 0; i < BANK_MAX; i++) {
                if (HAS_VOLATILE(i, VOLATILE_SEMI_INVULNERABLE))
                    OBJID_HIDE(gPkmnBank[i]->objid);
            }
            // spawn the HP boxes
            spawn_hpbox_opponent(HPBOX_TAG_OPP_SW, HPBOX_OPP_SW_X, HPBOX_OPP_SW_Y, OPPONENT_SINGLES_BANK);
            spawn_hpbox_player(HPBOX_TAG_PLAYER_SINGLE, HPBOX_PLAYER_SINGLE_X, HPBOX_PLAYER_SINGLE_Y, PLAYER_SINGLES_BANK);
            ShowBg(0);
            ShowBg(3);
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, 0x0000);
            gMain.state++;
            }
            break;
        case 2:
            if (!gPaletteFade.active) {
                // continue game callbacks
                // init textbox
                rbox_init_from_templates((struct TextboxTemplate*)&BattleTextBoxes[0]);
                LoadPalette((void*)stdpal_get(0), 16 * 7, 32);
                gMain.state++;
            }
            break;
        default:
            if (var_800E == 0) {
                BankSelectOption(PLAYER_SINGLES_BANK);
            } else {
                gPkmnBank[PLAYER_SINGLES_BANK]->battleData.isUsingItem = true;
                gPkmnBank[PLAYER_SINGLES_BANK]->battleData.last_used_item = var_800E;
                SetMainCallback(validate_player_selected_move);
            }
            break;
    };
}


void ReturnToBattleFromMoveMenu()
{
    switch (gMain.state) {
        case 0:
            if (gPaletteFade.active)
                return;
            // display
            lcd_io_set(0x4C, 0);
            REG_WININ = WININ_BUILD(WIN_BG0 | WIN_BG1 | WIN_BG2 | WIN_BG3 | WIN_OBJ | WIN_BLD,
            WIN_BG0 | WIN_BG1 | WIN_BG2 | WIN_BG3 | WIN_OBJ | WIN_BLD);
            rboxes_free();

            // callbacks
            HandlersClear();
            SetMainCallback(ReturnToBattleFromMoveMenu);
            SetMainCallback2((MainCallback)C2SyncAll);
            SetVBlankCallback((MainCallback)VblankMergeTextBox);

            // BG stuff
            u32 set = 0;
            CpuFastSet((void*)&set, (void*)ADDR_VRAM, CPUModeFS(0x10000, CPUFSSET));
            ResetPals();
            gpu_tile_bg_drop_all_sets(0);
            bg_vram_setup(0, (struct BgConfig *)&configBattleReturn, 4);
            // // init textbox
            rbox_init_from_templates((struct TextboxTemplate*)&BattleTextBoxes[0]);
            LoadPalette((void*)stdpal_get(0), 16 * 7, 32);
            // BGs
            pick_and_load_battle_bgs_no_entry(battle_textboxMap);
            HideBg(0);
            HideBg(1);
            HideBg(2);
            HideBg(3);
            gMain.state++;
            break;
        case 1:
            {
            // objs
            for (u8 i = 0; i < 0x3F; i++) {
                obj_free(&gSprites[i]);
            }
            NullBattleSpriteTracker();
            ResetSpriteData();
            gpu_tile_obj_tags_reset();
            // need to redraw gSprites
            create_sprites_battle_mons_wild();
            if (ACTIVE_BANK(OPPONENT_SINGLES_BANK))
                gSprites[gPkmnBank[OPPONENT_SINGLES_BANK]->objid].pos1.x = 178;
            // spawn the HP boxes
            if (ACTIVE_BANK(OPPONENT_SINGLES_BANK))
                spawn_hpbox_opponent(HPBOX_TAG_OPP_SW, HPBOX_OPP_SW_X, HPBOX_OPP_SW_Y, OPPONENT_SINGLES_BANK);
            if (ACTIVE_BANK(PLAYER_SINGLES_BANK))
                spawn_hpbox_player(HPBOX_TAG_PLAYER_SINGLE, HPBOX_PLAYER_SINGLE_X, HPBOX_PLAYER_SINGLE_Y, PLAYER_SINGLES_BANK);
            ShowBg(0);
            ShowBg(3);
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, 0x0000);
            gMain.state++;
            }
            break;
        case 2:
            if (!gPaletteFade.active) {
                // continue game callbacks
                gMain.state++;
            }
            break;
        case 3:
            SetMainCallback(AnimationMain);
            gMain.state = 0;
            break;
    };
}
