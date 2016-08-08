#############################################################################
# Makefile for building: Amerda
# Generated by qmake (2.01a) (Qt 4.8.5) on: ?? 8? 4 14:53:09 2016
# Project:  Amerda.pro
# Template: app
# Command: /bin/imx6-qmake -o Makefile Amerda.pro
#############################################################################

####### Compiler, tools and options

CC            = arm-fsl-linux-gnueabi-gcc
CXX           = arm-fsl-linux-gnueabi-g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/qws/linux-arm-g++ -I. -I/usr/local/Trolltech/QtEmbedded-4.8.5-arm/include/QtCore -I/usr/local/Trolltech/QtEmbedded-4.8.5-arm/include/QtNetwork -I/usr/local/Trolltech/QtEmbedded-4.8.5-arm/include/QtGui -I/usr/local/Trolltech/QtEmbedded-4.8.5-arm/include -I. -I. -I.
LINK          = arm-fsl-linux-gnueabi-g++
LFLAGS        = -Wl,-O1 -Wl,-rpath,/usr/local/Trolltech/QtEmbedded-4.8.5-arm/lib
LIBS          = $(SUBLIBS)  -L/usr/local/Trolltech/QtEmbedded-4.8.5-arm/lib -lQtGui -L/usr/local/Trolltech/QtEmbedded-4.8.5-arm/lib -lQtNetwork -lQtCore -lpthread 
AR            = arm-fsl-linux-gnueabi-ar cqs
RANLIB        = 
QMAKE         = /bin/imx6-qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = arm-fsl-linux-gnueabi-strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = amerdawidget.cpp \
		main.cpp \
		qcustomplot.cpp moc_amerdawidget.cpp \
		moc_qcustomplot.cpp
OBJECTS       = amerdawidget.o \
		main.o \
		qcustomplot.o \
		moc_amerdawidget.o \
		moc_qcustomplot.o
DIST          = /usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/unix.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/linux.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/gcc-base.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/gcc-base-unix.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/g++-base.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/g++-unix.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/qws.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/qconfig.pri \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/qt_functions.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/qt_config.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/exclusive_builds.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/default_pre.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/release.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/default_post.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/shared.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/warn_on.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/qt.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/unix/thread.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/moc.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/resources.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/uic.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/yacc.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/lex.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/include_source_dir.prf \
		Amerda.pro
QMAKE_TARGET  = Amerda
DESTDIR       = 
TARGET        = Amerda

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_amerdawidget.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: Amerda.pro  /usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/qws/linux-arm-g++/qmake.conf /usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/unix.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/linux.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/gcc-base.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/gcc-base-unix.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/g++-base.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/g++-unix.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/qws.conf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/qconfig.pri \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/qt_functions.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/qt_config.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/exclusive_builds.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/default_pre.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/release.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/default_post.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/shared.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/warn_on.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/qt.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/unix/thread.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/moc.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/resources.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/uic.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/yacc.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/lex.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/include_source_dir.prf \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/lib/libQtGui.prl \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/lib/libQtNetwork.prl \
		/usr/local/Trolltech/QtEmbedded-4.8.5-arm/lib/libQtCore.prl
	$(QMAKE) -o Makefile Amerda.pro
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/unix.conf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/linux.conf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/gcc-base.conf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/gcc-base-unix.conf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/g++-base.conf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/g++-unix.conf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/common/qws.conf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/qconfig.pri:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/qt_functions.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/qt_config.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/exclusive_builds.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/default_pre.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/release.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/default_post.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/shared.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/warn_on.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/qt.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/unix/thread.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/moc.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/resources.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/uic.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/yacc.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/lex.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/mkspecs/features/include_source_dir.prf:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/lib/libQtGui.prl:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/lib/libQtNetwork.prl:
/usr/local/Trolltech/QtEmbedded-4.8.5-arm/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile Amerda.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/Amerda1.0.0 || $(MKDIR) .tmp/Amerda1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/Amerda1.0.0/ && $(COPY_FILE) --parents amerdawidget.h qcustomplot.h .tmp/Amerda1.0.0/ && $(COPY_FILE) --parents amerdawidget.cpp main.cpp qcustomplot.cpp .tmp/Amerda1.0.0/ && $(COPY_FILE) --parents amerdawidget.ui .tmp/Amerda1.0.0/ && (cd `dirname .tmp/Amerda1.0.0` && $(TAR) Amerda1.0.0.tar Amerda1.0.0 && $(COMPRESS) Amerda1.0.0.tar) && $(MOVE) `dirname .tmp/Amerda1.0.0`/Amerda1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/Amerda1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_amerdawidget.cpp moc_qcustomplot.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_amerdawidget.cpp moc_qcustomplot.cpp
moc_amerdawidget.cpp: qcustomplot.h \
		amerdawidget.h
	/usr/local/Trolltech/QtEmbedded-4.8.5-arm/bin/moc $(DEFINES) $(INCPATH) amerdawidget.h -o moc_amerdawidget.cpp

moc_qcustomplot.cpp: qcustomplot.h
	/usr/local/Trolltech/QtEmbedded-4.8.5-arm/bin/moc $(DEFINES) $(INCPATH) qcustomplot.h -o moc_qcustomplot.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_amerdawidget.h
compiler_uic_clean:
	-$(DEL_FILE) ui_amerdawidget.h
ui_amerdawidget.h: amerdawidget.ui \
		qcustomplot.h
	/usr/local/Trolltech/QtEmbedded-4.8.5-arm/bin/uic amerdawidget.ui -o ui_amerdawidget.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

amerdawidget.o: amerdawidget.cpp amerdawidget.h \
		qcustomplot.h \
		ui_amerdawidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o amerdawidget.o amerdawidget.cpp

main.o: main.cpp amerdawidget.h \
		qcustomplot.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

qcustomplot.o: qcustomplot.cpp qcustomplot.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qcustomplot.o qcustomplot.cpp

moc_amerdawidget.o: moc_amerdawidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_amerdawidget.o moc_amerdawidget.cpp

moc_qcustomplot.o: moc_qcustomplot.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_qcustomplot.o moc_qcustomplot.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

