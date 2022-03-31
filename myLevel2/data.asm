.include "hdr.asm"

.section ".rodata1" superfree

mapgfx: .incbin "map_1_1.pic"
mapgfx_end:

map: .incbin "map_1_1.map"
map_end:

mappal: .incbin "map_1_1.pal"

snesfont: .incbin "mariofont.pic"
snesfont_end:

.ends


.section ".rodata2" superfree

mapcol: .incbin "map_1_1_col.clm"
mapcol_end:

.ends