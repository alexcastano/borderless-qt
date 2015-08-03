#include <QtGui>
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QtWidgets>
#endif

class TitleBar;

class MainFrame : public QFrame
{
public:
    MainFrame();

    // Allows you to access the content area of the frame
    // where widgets and layouts can be added
    QMainWindow *mainWindow() const { return mMainWindow; }

    TitleBar *titleBar() const { return mTitleBar; }

protected:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;


private:
    TitleBar *mTitleBar;
    QMainWindow *mMainWindow;

    QPoint  mClickedPos;
    QRect   mFrameGeometry;
    QSize   mMinSize;
    bool    mMousePressed;
    bool    mLeft;
    bool    mRight;
    bool    mTop;
    bool    mBottom;

private:
    static const int WINDOW_MARGIN = 5;
};

