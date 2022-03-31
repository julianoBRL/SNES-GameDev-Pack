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

map_1_1_col.clm: map_1_1_col.bmp
	@echo convert collision map ... $(notdir $@)
	$(GFXCONV) -pr -pc16 -n -gs8 -mc $<

mariofont.pic: mariofont.bmp
	@echo convert font with no tile reduction ... $(notdir $@)
	$(GFXCONV) -pc16 -n -gs8 -po2 -pe1 -mR! -m $<

#---------------------------------------------------------------------------------
bitmaps: map_1_1.pic mariofont.pic map_1_1_col.clm