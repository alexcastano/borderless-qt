#include "HoverMoveFilter.h"
#include "MainFrame.h"

HoverMoveFilter::HoverMoveFilter(QObject *parent) :
    QObject(parent)
{
}

bool HoverMoveFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::HoverMove) {
        QHoverEvent *mouseHoverEvent = static_cast<QHoverEvent *>(event);
        MainFrame* frame = static_cast<MainFrame *>(obj);
        QPoint pos = mouseHoverEvent->pos();
        frame->mouseMove(pos.x(), pos.y());
    }
    // standard event processing
    return QObject::eventFilter(obj, event);
}

