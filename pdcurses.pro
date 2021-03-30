TEMPLATE=lib
CONFIG+=warn_off

win32:DESTDIR=./lib
win32:OBJECTS_DIR=../.obj/win32/lib/pdcurses3_9
win32:INCLUDEPATH+=./lib/pdcurses3_9

win32:SOURCES += \
        lib/pdcurses3_9/pdcurses/addch.c \
        lib/pdcurses3_9/pdcurses/addchstr.c \
        lib/pdcurses3_9/pdcurses/addstr.c \
        lib/pdcurses3_9/pdcurses/attr.c \
        lib/pdcurses3_9/pdcurses/beep.c \
        lib/pdcurses3_9/pdcurses/bkgd.c \
        lib/pdcurses3_9/pdcurses/border.c \
        lib/pdcurses3_9/pdcurses/clear.c \
        lib/pdcurses3_9/pdcurses/color.c \
        lib/pdcurses3_9/pdcurses/debug.c \
        lib/pdcurses3_9/pdcurses/delch.c \
        lib/pdcurses3_9/pdcurses/deleteln.c \
        lib/pdcurses3_9/pdcurses/getch.c \
        lib/pdcurses3_9/pdcurses/getstr.c \
        lib/pdcurses3_9/pdcurses/getyx.c \
        lib/pdcurses3_9/pdcurses/inch.c \
        lib/pdcurses3_9/pdcurses/inchstr.c \
        lib/pdcurses3_9/pdcurses/initscr.c \
        lib/pdcurses3_9/pdcurses/inopts.c \
        lib/pdcurses3_9/pdcurses/insch.c \
        lib/pdcurses3_9/pdcurses/insstr.c \
        lib/pdcurses3_9/pdcurses/instr.c \
        lib/pdcurses3_9/pdcurses/kernel.c \
        lib/pdcurses3_9/pdcurses/keyname.c \
        lib/pdcurses3_9/pdcurses/mouse.c \
        lib/pdcurses3_9/pdcurses/move.c \
        lib/pdcurses3_9/pdcurses/outopts.c \
        lib/pdcurses3_9/pdcurses/overlay.c \
        lib/pdcurses3_9/pdcurses/pad.c \
        lib/pdcurses3_9/pdcurses/panel.c \
        lib/pdcurses3_9/pdcurses/printw.c \
        lib/pdcurses3_9/pdcurses/refresh.c \
        lib/pdcurses3_9/pdcurses/scanw.c \
        lib/pdcurses3_9/pdcurses/scr_dump.c \
        lib/pdcurses3_9/pdcurses/scroll.c \
        lib/pdcurses3_9/pdcurses/slk.c \
        lib/pdcurses3_9/pdcurses/termattr.c \
        lib/pdcurses3_9/pdcurses/touch.c \
        lib/pdcurses3_9/pdcurses/util.c \
        lib/pdcurses3_9/pdcurses/window.c \
        lib/pdcurses3_9/wincon/pdcclip.c \
        lib/pdcurses3_9/wincon/pdcdisp.c \
        lib/pdcurses3_9/wincon/pdcgetsc.c \
        lib/pdcurses3_9/wincon/pdckbd.c \
        lib/pdcurses3_9/wincon/pdcscrn.c \
        lib/pdcurses3_9/wincon/pdcsetsc.c \
        lib/pdcurses3_9/wincon/pdcutil.c

win32:HEADERS += \
       lib/pdcurses3_9/curses.h \
       lib/pdcurses3_9/curspriv.h \
       lib/pdcurses3_9/panel.h \
       lib/pdcurses3_9/wincon/pdcwin.h \
       lib/pdcurses3_9/common/acs437.h
