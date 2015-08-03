#include <QtGui>
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QtWidgets>
#endif

class TitleBar : public QWidget
{
Q_OBJECT
public:
    TitleBar(QWidget *parent);
    void titleChanged();

public slots:
    void showSmall() { parentWidget()->showMinimized(); }
    void showMaxRestore();

protected:
    void enterEvent(QEvent *e) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *me) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *me) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *me) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *me) Q_DECL_OVERRIDE;

    QLabel *mLabel;
    QToolButton *mMinimizeButton;
    QToolButton *mMaximizeButton;
    QToolButton *mCloseButton;
    QPixmap mRestorePix;
    QPixmap mMaxPix;
    bool mMaxNormal;
    QPoint mStartPos;
    QPoint mClickPos;
    bool mMouseButtonPressed;
};
