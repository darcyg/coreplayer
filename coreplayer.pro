TEMPLATE = subdirs

CONFIG -= ordered
libqtav.file = libQtAV/libQtAV.pro
EssentialDepends = avutil avcodec avformat swscale

SUBDIRS += libQtAV player

# Enable warnings and threading support
CONFIG += thread silent warn_off build_all

player.depends = libQtAVWidgets
!no-widgets {
  SUBDIRS += libQtAVWidgets
  libqtavwidgets.file = libQtAVWidgets/libQtAVWidgets.pro
  libqtavwidgets.depends = libqtav
}
# QtOpenGL module. In Qt5 we can disable it and still have opengl support
contains(QT_CONFIG, opengl):!no-gl:!no-widgets {
  greaterThan(QT_MAJOR_VERSION, 4):qtHaveModule(opengl):!config_gl {
    GL=config_gl done_config_gl
    cache(CONFIG, add, GL)
  } else {
    OptionalDepends *= gl
  }
}

unix:!mac {
  !android {
    !no-pulseaudio: OptionalDepends *= pulseaudio
    !no-x11:!no-widgets: OptionalDepends *= x11
    !no-xv:!no-widgets: OptionalDepends *= xv
    !no-vaapi: OptionalDepends *= vaapi
  }
  !no-cedarv: OptionalDepends *= libcedarv
}
