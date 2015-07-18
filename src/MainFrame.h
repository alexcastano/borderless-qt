#include <QtGui>
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QtWidgets>
#endif

#define WINDOW_MARGIN 5
class TitleBar;

class MainFrame : public QFrame
{
public:
    MainFrame();

    // Allows you to access the content area of the frame
    // where widgets and layouts can be added
    QMainWindow *mainWindow() const { return mMainWindow; }

    TitleBar *titleBar() const { return mTitleBar; }

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    void mouseMove(QPoint newPos, QPoint oldPos);

private:
    TitleBar *mTitleBar;
    QMainWindow *mMainWindow;
    QPoint mClickedPos;
    bool mMousePressed;
    bool left;
    bool right;
    bool bottom;
};

