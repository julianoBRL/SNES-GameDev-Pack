ifeq ($(strip $(PVSNESLIB_HOME)),)
$(error "Please create an environment variable PVSNESLIB_HOME with path to its folder and restart application. (you can do it on windows with <setx PVSNESLIB_HOME "/c/snesdev">)")
endif

include ${PVSNESLIB_HOME}/devkitsnes/snes_rules
 
.PHONY: bitmaps all
 
#---------------------------------------------------------------------------------
# ROMNAME is used in snes_rules file
export ROMNAME := myLevel

all: clean bitmaps $(ROMNAME).sfc

clean: cleanBuildRes cleanRom cleanGfx

map_1_1_col.clm: levels/1-1/map_1_1_col.bmp
	@echo convert collision map ... $(notdir $@)
	$(GFXCONV) -pr -pc16 -n -gs8 -mc $<

map_1_2_col.clm: levels/1-2/map_1_2_col.bmp
	@echo convert collision map ... $(notdir $@)
	$(GFXCONV) -pr -pc16 -n -gs8 -mc $<

snesfont.pic: sprites/snesfont.bmp
	@echo convert font with no tile reduction ... $(notdir $@)
	$(GFXCONV) -pc16 -n -gs8 -po2 -pe1 -mR! -m $<

player.pic: sprites/player.bmp
	@echo convert sprites ... $(notdir $@)
	$(GFXCONV) -gs16 -pc16 -po16 -n $<

#---------------------------------------------------------------------------------
bitmaps: levels/1-1/map_1_1.pic levels/1-2/map_1_2.pic snesfont.pic map_1_1_col.clm map_1_2_col.clm player.pic