#include "MainFrame.h"
#include "TitleBar.h"
#include "HoverMoveFilter.h"

MainFrame::MainFrame()
{
    mMousePressed = false;
    setFrameShape(Panel);

    // Make this a borderless window which can't
    // be resized or moved via the window system
    setWindowFlags(Qt::FramelessWindowHint);

    // Event tricks
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);
    installEventFilter(new HoverMoveFilter(this));

    mTitleBar = new TitleBar(this);

    mMainWindow = new QMainWindow(this);
    mMainWindow->setWindowFlags(Qt::Widget);

    // Creating action
    QAction *action = new QAction(QIcon::fromTheme("document-open"), tr("&Open..."), this);
    action->setShortcuts(QKeySequence::Open);
    action->setStatusTip(tr("Do nothing ;)"));

    // Creating toolbar
    QToolBar *toolbar = new QToolBar(mMainWindow);
    toolbar->addAction(action);
    mMainWindow->addToolBar(toolbar);

    // Creating menu
    QMenu *menu = mMainWindow->menuBar()->addMenu(tr("&File"));
    menu->addAction(action);

    // Creating dock
    QDockWidget *dockWidget = new QDockWidget(tr("Dock Widget"), this);
    QPushButton *pushButton = new QPushButton(QIcon::fromTheme("edit-undo"),"Panic",dockWidget);
    dockWidget->setWidget(pushButton);
    mMainWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidget);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->addWidget(mTitleBar);
    vbox->setMargin(0);
    vbox->setSpacing(0);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(mMainWindow);
    layout->setMargin(WINDOW_MARGIN);
    layout->setSpacing(0);
    vbox->addLayout(layout);
}

void MainFrame::mousePressEvent(QMouseEvent *e)
{
    mOldPos = e->pos();
    mMousePressed = e->button() == Qt::LeftButton;
}

void MainFrame::mouseReleaseEvent(QMouseEvent *e)
{
    mMousePressed = e->button() != Qt::LeftButton;
}

void MainFrame::mouseMove(int x, int y)
{
    if (mMousePressed) {
        int dx = x - mOldPos.x();
        int dy = y - mOldPos.y();

        QRect g = geometry();

        if (left)
            g.setLeft(g.left() + dx);
        if (right)
            g.setRight(g.right() + dx);
        if (bottom)
            g.setBottom(g.bottom() + dy);

        setGeometry(g);

        mOldPos = QPoint(!left ? x : mOldPos.x(), y);
    } else {
        QRect r = rect();
        left = qAbs(x - r.left()) <= WINDOW_MARGIN;
        right = qAbs(x - r.right()) <= WINDOW_MARGIN;
        bottom = qAbs(y - r.bottom()) <= WINDOW_MARGIN;
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
