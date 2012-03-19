#include "MainFrame.h"
#include "TitleBar.h"

MainFrame::MainFrame()
{
    m_mouse_down = false;
    setFrameShape(Panel);

    // Make this a borderless window which can't
    // be resized or moved via the window system
    setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);

    mTitleBar = new TitleBar(this);

    mMainWindow = new QMainWindow(this);
    mMainWindow->setWindowFlags(Qt::Widget);

    QAction *action = new QAction(QIcon::fromTheme("document-open"), tr("&Open..."), this);
    action->setShortcuts(QKeySequence::Open);
    action->setStatusTip(tr("Open an existing file"));

    QToolBar *toolbar = new QToolBar(mMainWindow);
    toolbar->addAction(action);
    mMainWindow->addToolBar(toolbar);

    QMenu *menu = mMainWindow->menuBar()->addMenu(tr("&File"));
    menu->addAction(action);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->addWidget(mTitleBar);
    vbox->setMargin(0);
    vbox->setSpacing(0);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(mMainWindow);
    layout->setMargin(5);
    layout->setSpacing(0);
    vbox->addLayout(layout);
}

void MainFrame::mousePressEvent(QMouseEvent *e)
{
    m_old_pos = e->pos();
    m_mouse_down = e->button() == Qt::LeftButton;
}

void MainFrame::mouseMoveEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = e->y();

    if (m_mouse_down) {
        int dx = x - m_old_pos.x();
        int dy = y - m_old_pos.y();

        QRect g = geometry();

        if (left)
            g.setLeft(g.left() + dx);
        if (right)
            g.setRight(g.right() + dx);
        if (bottom)
            g.setBottom(g.bottom() + dy);

        setGeometry(g);

        m_old_pos = QPoint(!left ? e->x() : m_old_pos.x(), e->y());
    } else {
        QRect r = rect();
        left = qAbs(x - r.left()) <= 5;
        right = qAbs(x - r.right()) <= 5;
        bottom = qAbs(y - r.bottom()) <= 5;
        bool hor = left | right;

        if (hor && bottom) {
            if (left)
                setCursor(Qt::SizeBDiagCursor);
            else
                setCursor(Qt::SizeFDiagCursor);
        } else if (hor) {
            setCursor(Qt::SizeHorCursor);
        } else if (bottom) {
            setCursor(Qt::SizeVerCursor);
        } else {
            setCursor(Qt::ArrowCursor);
        }
    }
}

void MainFrame::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    m_mouse_down = false;
}
