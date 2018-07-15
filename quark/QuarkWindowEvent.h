#pragma once

#include <QObject>

#include "EditObject.h"

class QEvent;

namespace qe {
    namespace edit {
        class QuarkWindowEvent : public QObject, public EditObject
        {
        public:
            explicit QuarkWindowEvent();
            ~QuarkWindowEvent();

        protected:
            bool eventFilter(QObject *obj, QEvent *event) override;

        };
    }
}







