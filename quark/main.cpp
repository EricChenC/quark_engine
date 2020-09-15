#include <QApplication>

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h> 

#include "EditWindow.h"

int main(int argc, char *argv[])
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(227223);

    QApplication a(argc, argv);

    qe::edit::EditWindow edit_window;

    edit_window.show();

    return a.exec();

}
