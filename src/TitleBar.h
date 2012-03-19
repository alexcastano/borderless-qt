#include <QtGui>

class TitleBar : public QWidget
{
Q_OBJECT
public:
    TitleBar(QWidget *parent);

public slots:
    void showSmall() { parentWidget()->showMinimized(); }
    void showMaxRestore();

protected:
    void mousePressEvent(QMouseEvent *me);
    void mouseMoveEvent(QMouseEvent *me);

private:
    QToolButton *minimize;
    QToolButton *maximize;
    QToolButton *close;
    QPixmap restorePix, maxPix;
    bool maxNormal;
    QPoint startPos;
    QPoint clickPos;
};
