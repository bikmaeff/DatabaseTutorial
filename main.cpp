#include <QApplication>
#include "mainwidget.h"

int main(int c, char **v)
{
    QApplication app(c, v);

    MainWidget mWid (NULL);

    mWid.show ();

    return app.exec();
}

