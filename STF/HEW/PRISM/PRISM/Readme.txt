-------- PROJECT GENERATOR --------
PROJECT NAME :	PRISM
PROJECT DIRECTORY :	C:\Users\Taiga Noumi\Desktop\My Dropbox\AOCSFramework2\STF\HEW\PRISM\PRISM
CPU SERIES :	SH-2
CPU TYPE :	SH7045F
TOOLCHAIN NAME :	Renesas SuperH RISC engine Standard Toolchain
TOOLCHAIN VERSION :	9.4.0.0
GENERATION FILES :
    C:\Users\Taiga Noumi\Desktop\My Dropbox\AOCSFramework2\STF\HEW\PRISM\PRISM\dbsct.c
        Setting of B,R Section
    C:\Users\Taiga Noumi\Desktop\My Dropbox\AOCSFramework2\STF\HEW\PRISM\PRISM\typedefine.h
        Aliases of Integer Type
    C:\Users\Taiga Noumi\Desktop\My Dropbox\AOCSFramework2\STF\HEW\PRISM\PRISM\sbrk.c
        Program of sbrk
    C:\Users\Taiga Noumi\Desktop\My Dropbox\AOCSFramework2\STF\HEW\PRISM\PRISM\iodefine.h
        Definition of I/O Register
    C:\Users\Taiga Noumi\Desktop\My Dropbox\AOCSFramework2\STF\HEW\PRISM\PRISM\intprg.c
        Interrupt Program
    C:\Users\Taiga Noumi\Desktop\My Dropbox\AOCSFramework2\STF\HEW\PRISM\PRISM\vecttbl.c
        Initialize of Vector Table
    C:\Users\Taiga Noumi\Desktop\My Dropbox\AOCSFramework2\STF\HEW\PRISM\PRISM\vect.h
        Definition of Vector
    C:\Users\Taiga Noumi\Desktop\My Dropbox\AOCSFramework2\STF\HEW\PRISM\PRISM\resetprg.c
        Reset Program
    C:\Users\Taiga Noumi\Desktop\My Dropbox\AOCSFramework2\STF\HEW\PRISM\PRISM\PRISM.cpp
        Main Program
    C:\Users\Taiga Noumi\Desktop\My Dropbox\AOCSFramework2\STF\HEW\PRISM\PRISM\sbrk.h
        Header file of sbrk file
    C:\Users\Taiga Noumi\Desktop\My Dropbox\AOCSFramework2\STF\HEW\PRISM\PRISM\stacksct.h
        Setting of Stack area
START ADDRESS OF SECTION :
 H'000000000	DVECTTBL,DINTTBL
 H'000000500	PResetPRG,PIntPRG
 H'000001000	P,C,C$BSEC,C$DSEC,C$INIT,D
 H'0FFFFF000	B,R
 H'0FFFFF7E0	S

* When the user program is executed,
* the interrupt mask has been masked.
* 
* Program start H'1000.
* RAM start H'FFFFF000.

SELECT TARGET :
    SH-2 Simulator
DATE & TIME : 2011/03/22 14:34:03
