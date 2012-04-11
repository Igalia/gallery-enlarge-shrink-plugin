TEMPLATE        = lib
QMAKE_LFLAGS   += -Wl,--as-needed
QMAKE_CXXFLAGS += -Werror -Wall -W
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3 -fvisibility=hidden
QMAKE_CXXFLAGS_DEBUG += -O0 -ggdb
CONFIG         += plugin \
                  quillimagefilter

contains( debug, yes ) {
    message( "Configuring for debug build ..." )
    CONFIG += debug warn_on
} else {
    message( "Configuring for release build ..." )
    CONFIG += release warn_on
    DEFINES += QT_NO_DEBUG_OUTPUT
}

HEADERS += quillenlargeshrinkplugin.h \
           enlargeshrink.h

SOURCES += quillenlargeshrinkplugin.cpp \
           enlargeshrink.cpp

target.path = $$[QT_INSTALL_PLUGINS]/quillimagefilters
INSTALLS += target

