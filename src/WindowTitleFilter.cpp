#include "WindowTitleFilter.h"
#include "MainFrame.h"
#include "TitleBar.h"

WindowTitleFilter::WindowTitleFilter(QObject *parent) :
    QObject(parent)
{
}

bool WindowTitleFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::WindowTitleChange) {
        MainFrame* frame = static_cast<MainFrame *>(obj);
        frame->titleBar()->titleChanged();
    }
    // standard event processing
    return QObject::eventFilter(obj, event);
}

