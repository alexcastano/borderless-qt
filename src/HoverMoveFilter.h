#ifndef HOVERMOVEFILTER_H
#define HOVERMOVEFILTER_H

#include <QObject>

class HoverMoveFilter : public QObject
{
    Q_OBJECT;
    public:
    HoverMoveFilter(QObject* parent);

    protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // HOVERMOVEFILTER_H
