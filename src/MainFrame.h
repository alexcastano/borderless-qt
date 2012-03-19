#include <QtGui>

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

    void mouseMoveEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);

private:
    TitleBar *mTitleBar;
    QMainWindow *mMainWindow;
    QPoint m_old_pos;
    bool m_mouse_down;
    bool left, right, bottom;
};

