#pragma once

#if __has_include(<QApplication>)
    #include "qt.h"
#endif

#if __has_include(<wx/wx.h>)
    #include "wx.h"
#endif

#if __has_include(<nana/gui.hpp>)
    #include "nana.h"
#endif
