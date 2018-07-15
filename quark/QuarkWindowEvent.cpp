#include "QuarkWindowEvent.h"

#include <QEvent>

#include <iostream>

qe::edit::QuarkWindowEvent::QuarkWindowEvent()
{
}

qe::edit::QuarkWindowEvent::~QuarkWindowEvent()
{
}

bool qe::edit::QuarkWindowEvent::eventFilter(QObject * obj, QEvent * event)
{
    if (event->type() == QEvent::DragEnter) {
        std::cout << "drag enter \n";
        return true;
    }
    else if(event->type() == QEvent::Drop)
    {
        std::cout << "drop \n";
        return true;
    }
    else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }

    return false;
}
