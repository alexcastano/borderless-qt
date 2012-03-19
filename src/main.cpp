#include <QtGui>

class TitleBar : public QWidget
{
Q_OBJECT
public:

    TitleBar(QWidget *parent)
    {
        // Don't let this widget inherit the parent's backround color
        setAutoFillBackground(true);
        // Use a brush with a Highlight color role to render the background
        setBackgroundRole(QPalette::Highlight);

        minimize = new QToolButton(this);
        maximize = new QToolButton(this);
        close= new QToolButton(this);

        // Use the style to set the button pixmaps
        QPixmap pix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
        close->setIcon(pix);

        maxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
        maximize->setIcon(maxPix);

        pix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
        minimize->setIcon(pix);

        restorePix = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);

        minimize->setMinimumHeight(20);
        close->setMinimumHeight(20);
        maximize->setMinimumHeight(20);


        QLabel *label = new QLabel(this);
        label->setText("Window Title");
        parent->setWindowTitle("Window Title");

        QHBoxLayout *hbox = new QHBoxLayout(this);

        hbox->addWidget(label);
        hbox->addWidget(minimize);
        hbox->addWidget(maximize);
        hbox->addWidget(close);

        hbox->insertStretch(1, 500);
        hbox->setSpacing(0);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        maxNormal = false;

        connect(close, SIGNAL( clicked() ), parent, SLOT(close() ) );
        connect(minimize, SIGNAL( clicked() ), this, SLOT(showSmall() ) );
        connect(maximize, SIGNAL( clicked() ), this, SLOT(showMaxRestore() ) );
    }

public slots:
    void showSmall()
    {
        parentWidget()->showMinimized();
    }

    void showMaxRestore()
    {
        if (maxNormal) {
            parentWidget()->showNormal();
            maxNormal = !maxNormal;
            maximize->setIcon(maxPix);
        } else {
            parentWidget()->showMaximized();
            maxNormal = !maxNormal;
            maximize->setIcon(restorePix);
        }
    }
protected:
    void mousePressEvent(QMouseEvent *me)
    {
        startPos = me->globalPos();
        clickPos = mapToParent(me->pos());
    }
    void mouseMoveEvent(QMouseEvent *me)
    {
        if (maxNormal)
            return;
        parentWidget()->move(me->globalPos() - clickPos);
    }

private:
    QToolButton *minimize;
    QToolButton *maximize;
    QToolButton *close;
    QPixmap restorePix, maxPix;
    bool maxNormal;
    QPoint startPos;
    QPoint clickPos;
};

class Frame : public QFrame
{
public:
    Frame()
    {
        m_mouse_down = false;
        setFrameShape(Panel);

        // Make this a borderless window which can't
        // be resized or moved via the window system
        setWindowFlags(Qt::FramelessWindowHint);
        setMouseTracking(true);

        m_titleBar = new TitleBar(this);

        m_content = new QWidget(this);

        QVBoxLayout *vbox = new QVBoxLayout(this);
        vbox->addWidget(m_titleBar);
        vbox->setMargin(0);
        vbox->setSpacing(0);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(m_content);
        layout->setMargin(5);
        layout->setSpacing(0);
        vbox->addLayout(layout);
    }

    // Allows you to access the content area of the frame
    // where widgets and layouts can be added
    QWidget *contentWidget() const { return m_content; }

    TitleBar *titleBar() const { return m_titleBar; }

    void mousePressEvent(QMouseEvent *e)
    {
        m_old_pos = e->pos();
        m_mouse_down = e->button() == Qt::LeftButton;
    }

    void mouseMoveEvent(QMouseEvent *e)
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

    void mouseReleaseEvent(QMouseEvent *e)
    {
        Q_UNUSED(e);
        m_mouse_down = false;
    }

private:
    TitleBar *m_titleBar;
    QWidget *m_content;
    QPoint m_old_pos;
    bool m_mouse_down;
    bool left, right, bottom;
};


#include "main.moc"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Frame box;
    box.move(0,0);

    QVBoxLayout *l = new QVBoxLayout(box.contentWidget());
    l->setMargin(0);
    QTextEdit *edit = new QTextEdit(box.contentWidget());
    l->addWidget(edit);

    box.show();
    return app.exec();
}
