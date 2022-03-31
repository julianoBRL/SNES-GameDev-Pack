.include "hdr.asm"

.section ".rodata1" superfree

    mapgfx: .incbin "levels/1-1/map_1_1.pic"
    mapgfx_end:

    map: .incbin "levels/1-1/map_1_1.map"
    map_end:

    mappal: .incbin "levels/1-1/map_1_1.pal"

    mapcol: .incbin "levels/1-1/map_1_1_col.clm"
    mapcol_end:

.ends

.section ".rodata2" superfree

    mapgfx2: .incbin "levels/1-2/map_1_2.pic"
    mapgfx2_end:

    map2: .incbin "levels/1-2/map_1_2.map"
    map2_end:

    mappal2: .incbin "levels/1-2/map_1_2.pal"

    mapcol2: .incbin "levels/1-2/map_1_2_col.clm"
    mapcol2_end:

.ends


.section ".rodata7" superfree

    playergfx: .incbin "sprites/player.pic"
    playergfx_end:

    playerpal: .incbin "sprites/player.pal"

    snesfont: .incbin "sprites/snesfont.pic"
    snesfont_end:

.ends