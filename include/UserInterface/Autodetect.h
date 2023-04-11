#include "RegisterToolkit.h"

#if __has_include(<QApplication>)
    #include "Qt.h"
UserInterface_RegisterToolkit(Qt, UserInterface::Qt::Toolkit);
#endif

#if __has_include(<wx/wx.h>)
    #include "wxWidgets.h"
UserInterface_RegisterToolkit(wxWidgets, UserInterface::wxWidgets::Toolkit);
#endif

#if __has_include(<nana/gui.hpp>)
    #include "Nana.h"
UserInterface_RegisterToolkit(Nana, UserInterface::Nana::Toolkit);
#endif
