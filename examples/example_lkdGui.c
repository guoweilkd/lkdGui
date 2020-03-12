#include <rtthread.h>
#include <finsh.h>

#include "lkdGui.h"

int lkdGui_test(int argc, char** argv)
{
    GuiClearScreen(GuiGetbackcolor());
    OpenLcdDisplay();
    GuiUpdateDisplayAll();

    GuiRect(5, 5, 30,30, GuiGetForecolor());

    return 0;
}
MSH_CMD_EXPORT(lkdGui_test, lkdGui API test);
