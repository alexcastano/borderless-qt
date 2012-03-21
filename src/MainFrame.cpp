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
    // mOldPos = e->pos();
    mMousePressed = e->button() == Qt::LeftButton;
    if (mMousePressed) {
        if (left) {
            mClickedPos.setX(e->pos().x());
        }
        if (right) {
            mClickedPos.setX(width() - e->pos().x());
        }
        if (bottom) {
            mClickedPos.setY(height() - e->pos().y());
        }
    }
}

void MainFrame::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mMousePressed = false;
    }
}

void MainFrame::mouseMove(QPoint newPos, QPoint oldPos)
{
    if (mMousePressed) {
        int dx = newPos.x() - oldPos.x();
        int dy = newPos.y() - oldPos.y();

        QRect g = geometry();
        QSize minSize = minimumSize();

        // We don't resize if the windows has the minimum size
        if (left) {
            // Fix a bug when you try to resize to less than minimum size and
            // then the mouse goes right again.
            if (dx < 0 && oldPos.x() > mClickedPos.x() ) {
                dx += oldPos.x() - mClickedPos.x();
                if (dx > 0) {
                    dx = 0;
                }
            } else if ( dx > 0 && g.width() - dx < minSize.width()) {
                dx = g.width() - minSize.width();
            }
            g.setLeft(g.left() + dx);
        }

        if (right) {
            // Fix a bug when you try to resize to less than minimum size and
            // then the mouse goes right again.
            if (dx > 0 && (width() - newPos.x() > mClickedPos.x())) {
                dx -= width() - newPos.x() - mClickedPos.x();
                if (dx < 0) {
                    dx = 0;
                }
            }
            g.setRight(g.right() + dx);
        }
        if (bottom) {
            // Fix a bug when you try to resize to less than minimum size and
            // then the mouse goes down again.
            if (dy > 0 && (height() - newPos.y() > mClickedPos.y())) {
                dy -= height() - newPos.y() - mClickedPos.y();
                if (dy < 0) {
                    dy = 0;
                }
            }
            g.setBottom(g.bottom() + dy);
        }

        setGeometry(g);

    } else {
        QRect r = rect();
        left = qAbs(newPos.x()- r.left()) <= WINDOW_MARGIN;
        right = qAbs(newPos.x() - r.right()) <= WINDOW_MARGIN;
        bottom = qAbs(newPos.y() - r.bottom()) <= WINDOW_MARGIN;
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
