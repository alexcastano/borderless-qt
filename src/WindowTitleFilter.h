#ifndef WINDOWTITLEFILTER_H
#define WINDOWTITLEFILTER_H

#include <QObject>

class WindowTitleFilter : public QObject
{
Q_OBJECT;
public:
    WindowTitleFilter(QObject* parent);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // WINDOWTITLEFILTER_H
