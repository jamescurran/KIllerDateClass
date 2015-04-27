CFLAGS      = /D_DOS /AM /W3 /Zp /Gs /c
LFLAGS      = /NOD /ONERROR:NOEXE

OBJS        = datedemo.obj datecl.obj

datedemo.exe    : $(OBJS)
    link $(LFLAGS) datedemo datecl, datedemo, NUL, mlibce;

datedemo.obj    : datedemo.cpp datecl.h
    cl $(CFLAGS) datedemo.cpp

datecl.obj     : datecl.cpp datecl.h
    cl $(CFLAGS) datecl.cpp

