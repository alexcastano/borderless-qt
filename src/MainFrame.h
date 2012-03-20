#include <QtGui>

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

    void mouseMove(int x, int y);

private:
    TitleBar *mTitleBar;
    QMainWindow *mMainWindow;
    QPoint mOldPos;
    bool mMousePressed;
    bool left;
    bool right;
    bool bottom;
};

