#include "MainFrame.h"
#include "TitleBar.h"
#include "WindowTitleFilter.h"

namespace Private {

    /**
    * @internal
    *
    * @class Private::WindowEventFilter
    *
    * @brief            Event filter for the frame's child widget (the main Window).
    *
    * @param filtered   the filtered widget
    *
    * @param parent     the parent takes ownership of this event filter object
    *
    */
    class WindowEventFilter : public QObject
    {
    public:
        WindowEventFilter(QWidget* filtered, QObject* parent)
            : QObject(parent)
            , mFiltered(filtered)
        {
            Q_ASSERT(filtered && parent);
            filtered->installEventFilter(this);
        }

    private:
        bool eventFilter(QObject* o, QEvent* e)
        {
            Q_ASSERT(o == mFiltered);

            switch (e->type()) {
            default: break;

            case QEvent::Enter:
            case QEvent::Leave:
                mFiltered->setCursor(Qt::ArrowCursor);
                break;
            }

            return QObject::eventFilter(o, e);
        }

    private:
        QWidget* mFiltered;
    };

}

MainFrame::MainFrame()
    : QFrame(0, Qt::FramelessWindowHint)
{
    mLeft = mRight = mTop = mBottom = false;
    mMousePressed = false;
    setFrameShape(Panel);

    // Event tricks
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);

    // Get title changes
    installEventFilter(new WindowTitleFilter(this));

    // Title
    mTitleBar = new TitleBar(this);
    setWindowTitle("Borderless window");

    mMainWindow = new QMainWindow(this);
    mMainWindow->setWindowFlags(Qt::Widget);
    new Private::WindowEventFilter(mMainWindow, this);

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
    if (e->button() != Qt::LeftButton) {
        return QFrame::mousePressEvent(e);
    }

    mMousePressed = true;
    mClickedPos = e->globalPos();
    mFrameGeometry = geometry();
    mMinSize = minimumSizeHint();

    if (cursor().shape() != Qt::ArrowCursor) {
        setWindowTitle("Resizing");
    }
}

void MainFrame::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() != Qt::LeftButton) {
        return QFrame::mousePressEvent(e);
    }

    mMousePressed = false;
    mFrameGeometry = QRect();
    mClickedPos = QPoint();
    setWindowTitle("Borderless window");
}

void MainFrame::mouseMoveEvent(QMouseEvent* e)
{
    if (mMousePressed) {
        const int dx = e->globalPos().x() - mClickedPos.x();
        const int dy = e->globalPos().y() - mClickedPos.y();

        QRect g = mFrameGeometry;

        // don't resize if the window reached the minimum size
        if (mLeft) {
            g.setLeft(g.left() + dx);
        } else if (mRight) {
            g.setRight(g.right() + dx);
        }

        if (mTop) {
            g.setTop(g.top() + dy);
        } else if (mBottom) {
            g.setBottom(g.bottom() + dy);
        }

        if (g.width() > mMinSize.width() && g.height() > mMinSize.height()) {
            setGeometry(g);
        }
    } else {
        const QRect r = frameRect();
        const int px = e->pos().x();
        const int py = e->pos().y();

        mLeft   = px <= WINDOW_MARGIN && px >= 0;
        mRight  = px >= r.right() - WINDOW_MARGIN && px <= r.right();
        mTop    = py <= WINDOW_MARGIN && py >= 0;
        mBottom = py >= r.bottom() - WINDOW_MARGIN && py <= r.bottom();

        bool hor = mLeft || mRight;

        if (mBottom) {
            if (mLeft) {
                setCursor(Qt::SizeBDiagCursor);
            } else if (mRight) {
                setCursor(Qt::SizeFDiagCursor);
            } else {
                setCursor(Qt::SizeVerCursor);
            }
        } else if (mTop) {
            if (mLeft) {
                setCursor(Qt::SizeFDiagCursor);
            } else if (mRight) {
                setCursor(Qt::SizeBDiagCursor);
            } else {
                setCursor(Qt::SizeVerCursor);
            }
        } else if (hor) {
            setCursor(Qt::SizeHorCursor);
        }
    }

    QFrame::mouseMoveEvent(e);
}
