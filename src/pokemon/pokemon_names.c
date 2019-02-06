#include <pokeagb/pokeagb.h>

const u8 gSpeciesNames[][POKEMON_NAME_LENGTH + 1] = {
    _("??????????"),
    _("Horsea"),
    _("Seadra"),
    _("Kingdra"),
    _("Trapinch"),
    _("Vibrava"),
    _("Flygon"),
    _("Togepi"),
    _("Togetic"),
    _("Togekiss"),
    _("Yungoos"),
    _("Gumshoos"),
    _("Bunnelby"),
    _("Diggersby"),
    _("Bounsweet"),
    _("Steenee"),
    _("Tsareena"),
    _("Mareep"),
    _("Flaaffy"),
    _("Ampharos"),
    _("Combee"),
    _("Vespiquen"),
    _("Spinarak"),
    _("Ariados"),
    _("Joltik"),
    _("Galvantula"),
    _("Dewpider"),
    _("Araquanid"),
    _("Zubat"),
    _("Golbat"),
    _("Crobat"),
    _("Yanma"),
    _("Yanmega"),
    _("Morelull"),
    _("Shiinotic"),
    _("Vulpix"),
    _("Ninetales"),
    _("Growlithe"),
    _("Arcanine"),
    _("Pineco"),
    _("Forretress"),
    _("Nincada"),
    _("Ninjask"),
    _("Shedinja"),
    _("Feebas"),
    _("Milotic"),
    _("Shellder"),
    _("Cloyster"),
    _("Slowpoke"),
    _("Slowbro"),
    _("Slowking"),
    _("Abra"),
    _("Kadabra"),
    _("Alakazam"),
    _("Espurr"),
    _("Meowstic"),
    _("Cottonee"),
    _("Whimsicott"),
    _("Petilil"),
    _("Lilligant"),
    _("Shroomish"),
    _("Breloom"),
    _("Swablu"),
    _("Altaria"),
    _("Murkrow"),
    _("Honchkrow"),
    _("Cleffa"),
    _("Clefairy"),
    _("Clefable"),
    _("Riolu"),
    _("Lucario"),
    _("Machop"),
    _("Machoke"),
    _("Machamp"),
    _("Shinx"),
    _("Luxio"),
    _("Luxray"),
    _("Litleo"),
    _("Pyroar"),
    _("Houndour"),
    _("Houndoom"),
    _("Wingull"),
    _("Pelliper"),
    _("Tentacool"),
    _("Tentacruel"),
    _("Remoraid"),
    _("Octillery"),
    _("Inkay"),
    _("Malamar"),
    _("Dwebble"),
    _("Crustle"),
    _("Skrelp"),
    _("Dragalge"),
    _("Trubbish"),
    _("Garbodor"),
    _("Croagunk"),
    _("Toxicroak"),
    _("Skorupi"),
    _("Drapion"),
    _("Carnivine"),
    _("Goomy"),
    _("Sliggoo"),
    _("Goodra"),
    _("Mudbray"),
    _("Mudsdale"),
    _("Gastly"),
    _("Haunter"),
    _("Gengar"),
    _("Duskull"),
    _("Dusclops"),
    _("Dusknoir"),
    _("Noibat"),
    _("Noivern"),
    _("Dunsparce"),
    _("Mienfoo"),
    _("Mienshao"),
    _("Blitzle"),
    _("Zebstrika"),
    _("Ponyta"),
    _("Rapidash"),
    _("Heracross"),
    _("Scyther"),
    _("Scizor"),
    _("Eevee"),
    _("Vaporeon"),
    _("Jolteon"),
    _("Flareon"),
    _("Espeon"),
    _("Umbreon"),
    _("Leafeon"),
    _("Glaceon"),
    _("Sylveon"),
    _("Rockruff"),
    _("Lycanroc"),
    _("Geodude"),
    _("Graveler"),
    _("Golem"),
    _("Anorith"),
    _("Armaldo"),
    _("Lileep"),
    _("Cradily"),
    _("Chinchou"),
    _("Lanturn"),
    _("Staryu"),
    _("Starmie"),
    _("Spheal"),
    _("Sealeo"),
    _("Walrein"),
    _("Pawniard"),
    _("Bisharp"),
    _("Scraggy"),
    _("Scrafty"),
    _("Gligar"),
    _("Gliscor"),
    _("Skiddo"),
    _("Gogoat"),
    _("Drampa"),
    _("Larvitar"),
    _("Pupitar"),
    _("Tyranitar"),
    _("Salandit"),
    _("Salazzle"),
    _("Sandile"),
    _("Krokorok"),
    _("Krookodile"),
    _("Sigilyph"),
    _("Maractus"),
    _("Cacnea"),
    _("Cacturne"),
    _("Shuckle"),
    _("Slugma"),
    _("Magcargo"),
    _("Torkoal"),
    _("Turtonator"),
    _("Larvesta"),
    _("Volcarona"),
    _("Swirlix"),
    _("Slurpuff"),
    _("Comfey"),
    _("Klefki"),
    _("Tynamo"),
    _("Eelektrik"),
    _("Eelektross"),
    _("Magnemite"),
    _("Magneton"),
    _("Magnezone"),
    _("Dedenne"),
    _("Togedemaru"),
    _("Mimikyu"),
    _("Rotom"),
    _("Sandygast"),
    _("Palossand"),
    _("Litwick"),
    _("Lampent"),
    _("Chandelure"),
    _("Dhelmise"),
    _("Honedge"),
    _("Doublade"),
    _("Aegislash"),
    _("SpiritTomb"),
    _("Mawile"),
    _("Girafarig"),
    _("Munchlax"),
    _("Snorlax"),
    _("Pancham"),
    _("Pangoro"),
    _("Passimian"),
    _("Stufful"),
    _("Bewear"),
    _("Bouffalant"),
    _("Kangaskhan"),
    _("Hawlucha"),
    _("Tropius"),
    _("Lapras"),
    _("Skarmory"),
    _("Sneasel"),
    _("Weavile"),
    _("Snover"),
    _("Abomasnow"),
    _("Snorunt"),
    _("Glalie"),
    _("Froslass"),
    _("Bergmite"),
    _("Avalugg"),
    _("Cryogonal"),
    _("Porygon"),
    _("Porygon2"),
    _("Porygon-Z"),
    _("Druddigon"),
    _("Golett"),
    _("Golurk"),
    _("Drilbur"),
    _("Excadrill"),
    _("Beldum"),
    _("Metang"),
    _("Metagross"),
    _("Gible"),
    _("Gabite"),
    _("Garchomp"),
    _("Dratini"),
    _("Dragonair"),
    _("Dragonite"),
    _("Latias"),
    _("Latios"),
    _("Heatran"),
    _("Deoxys"),
    _("Jirachi"),
    _("Darkrai"),

};


void GetSpeciesName(u8 *name, u16 species)
{
    s32 i;
    for (i = 0; i <= POKEMON_NAME_LENGTH; i++) {
        name[i] = gSpeciesNames[species][i];
        if (name[i] == 0xFF)
            break;
    }
    name[i] = 0xFF;
}
