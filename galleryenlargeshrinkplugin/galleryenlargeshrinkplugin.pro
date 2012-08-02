TEMPLATE        = lib
QMAKE_LFLAGS   += -Wl,--as-needed
QMAKE_CXXFLAGS += -Werror -Wall -W
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3 -fvisibility=hidden
QMAKE_CXXFLAGS_DEBUG += -O0 -ggdb
CONFIG         += plugin \
                  meegotouch \
                  gallerycore \
                  quillimagefilter

contains( debug, yes ) {
    message( "Configuring for debug build ..." )
    CONFIG += debug warn_on
} else {
    message( "Configuring for release build ..." )
    CONFIG += release warn_on
    DEFINES += QT_NO_DEBUG_OUTPUT
}

PACKAGEVERSION = $$system(head -n 1 ../debian/changelog | grep -o [0-9].[0-9].[0-9])
DEFINES += "PACKAGEVERSION=\\\"$$PACKAGEVERSION\\\""

HEADERS += galleryenlargeshrinkplugin.h \
           galleryenlargeshrinkplugin_p.h \
           galleryenlargeshrinkwidget.h \
           galleryenlargeshrinkwidget_p.h \
           galleryenlargeshrinkaboutwidget.h

SOURCES += galleryenlargeshrinkplugin.cpp \
           galleryenlargeshrinkwidget.cpp \
           galleryenlargeshrinkaboutwidget.cpp

OTHER_FILES += \
           conf/libgalleryenlargeshrinktplugin.css

target.path = /usr/lib/gallery

include($$[QT_INSTALL_DATA]/mkspecs/features/meegotouch_defines.prf)
meegotouch.files = conf/libgalleryenlargeshrinkplugin.css
meegotouch.path = $${M_THEME_DIR}/base/meegotouch/libgalleryenlargeshrinkplugin/style

editicon.files = data/icon-m-image-edit-enlarge-shrink.png
editicon.path = /usr/share/themes/base/meegotouch/icons

icon.files = data/icon-l-enlarge-shrink.png
icon.path = /usr/share/icons/hicolor/64x64/apps/

INSTALLS += target meegotouch editicon icon
