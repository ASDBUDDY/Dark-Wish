.text
.thumb
.align 2
.include "src/animation_cmds.s"

.global ShowAttackerAnimation
ShowAttackerAnimation:
    fastsetbattlers
    showsprite attacker
    end
.pool
