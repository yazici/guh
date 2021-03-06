# Parse and export GUH_VERSION_STRING
GUH_VERSION_STRING=$$system('dpkg-parsechangelog | sed -n -e "s/^Version: //p"')
DEFINES += GUH_VERSION_STRING=\\\"$${GUH_VERSION_STRING}\\\"

QMAKE_CXXFLAGS += -Werror
CONFIG += c++11

# Enable coverage option    
coverage {
    QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage -O0
    LIBS += -lgcov
    QMAKE_LFLAGS += -fprofile-arcs
}

top_srcdir=$$PWD
top_builddir=$$shadowed($$PWD)

