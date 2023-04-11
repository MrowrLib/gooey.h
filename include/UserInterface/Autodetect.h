#pragma once

#if __has_include(<QApplication>)
    #include "Qt.h"
#endif

#if __has_include(<wx/wx.h>)
    #include "wxWidgets.h"
#endif

#if __has_include(<nana/gui.hpp>)
    #include "Nana.h"
#endif
