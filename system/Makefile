TOOLPATH = ../z_tools/
MAKE     = $(TOOLPATH)make.exe -r
NAJC     = $(TOOLPATH)NAJC.exe
CC1      = $(TOOLPATH)cc1.exe -I$(INCPATH) -Os -Wall -quiet
GAS2NAJC = $(TOOLPATH)gas2najc.exe -a
OBJ2BIM  = $(TOOLPATH)obj2bim.exe
BIM2HRB  = $(TOOLPATH)bim2hrb.exe
RULEFILE = $(TOOLPATH)jc/jc.rul
EDIMG    = $(TOOLPATH)edimg.exe
IMGTOL   = $(TOOLPATH)imgtol.com
COPY     = copy
DEL      = del


default :
	$(MAKE) img

boot.bin : boot.ajc Makefile
	$(NAJC) -f boot.ajc -o boot.bin

bootjc.bin : bootjc.ajc Makefile
	$(NAJC) -f bootjc.ajc -o bootjc.bin

bootpack.gas : bootpack.c Makefile
	$(CC1) -o bootpack.gas bootpack.c

bootpack.ajc : bootpack.gas Makefile
	$(GAS2NAJC) bootpack.gas bootpack.ajc

bootpack.obj : bootpack.ajc Makefile
	$(NAJC) -f bootpack.ajc -o bootpack.obj

jcfunc.obj : jcfunc.ajc Makefile
	$(NAJC) -f jcfunc.ajc -o jcfunc.obj

bootpack.bim : bootpack.obj jcfunc.obj Makefile
	$(OBJ2BIM) @$(RULEFILE) out:bootpack.bim stack:3136k map:bootpack.map \
		bootpack.obj jcfunc.obj

bootpack.hrb : bootpack.bim Makefile
	$(BIM2HRB) bootpack.bim bootpack.hrb 0

bootjc.sys : bootjc.bin bootpack.hrb Makefile
	copy /B bootjc.bin+bootpack.hrb bootjc.sys

SystemJC.img : boot.bin bootjc.sys Makefile
	$(EDIMG) imgin:../z_tools/fdimg0at.tek wbinimg src:boot.bin len:512 from:0 to:0 copy from:bootjc.sys to:@: imgout:SystemJC.img

asm :
	$(MAKE) boot.bin

img :
	$(MAKE) SystemJC.img

run :
	$(MAKE) img
	$(COPY) SystemJC.img ..\z_tools\qemu\fdimage0.bin
	$(MAKE) -C ../z_tools/qemu

install :
	$(MAKE) img
	$(IMGTOL) w a: SystemJC.img

clean :
	-$(DEL) *.bin
	-$(DEL) *.gas
	-$(DEL) *.obj
	-$(DEL) bootpack.ajc
	-$(DEL) bootpack.map
	-$(DEL) bootpack.bim
	-$(DEL) bootpack.hrb
	-$(DEL) bootjc.sys

src_only :
	$(MAKE) clean
	-$(DEL) SystemJC.img
