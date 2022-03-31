.include "hdr.asm"

.section ".rodata3" superfree
gfxpsrite:
.incbin "sprites.pic"
gfxpsrite_end:
.ends

.section ".rodata2" superfree
palsprite:
.incbin "sprites.pal"
palsprite_end:
.ends