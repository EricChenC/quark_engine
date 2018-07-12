#include <QApplication>

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h> 

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(227223);

    QApplication a(argc, argv);

    qe::edit::MainWindow main_window;

    main_window.show();

    return a.exec();

}
