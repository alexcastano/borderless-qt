#include "TitleBar.h"

TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{
    // Don't let this widget inherit the parent's backround color
    setAutoFillBackground(true);
    // Use a brush with a Highlight color role to render the background
    setBackgroundRole(QPalette::Highlight);


    mMinimizeButton = new QToolButton(this);
    mMaximizeButton = new QToolButton(this);
    mCloseButton= new QToolButton(this);

    // Use the style to set the button pixmaps
    QPixmap pix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    mCloseButton->setIcon(pix);

    mMaxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
    mMaximizeButton->setIcon(mMaxPix);

    pix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    mMinimizeButton->setIcon(pix);

    mRestorePix = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);

    mMinimizeButton->setMinimumHeight(20);
    mCloseButton->setMinimumHeight(20);
    mMaximizeButton->setMinimumHeight(20);


    mLabel = new QLabel(this);
    mLabel->setText(parent->windowTitle());

    QHBoxLayout *hbox = new QHBoxLayout(this);

    hbox->addWidget(mLabel);
    hbox->addWidget(mMinimizeButton);
    hbox->addWidget(mMaximizeButton);
    hbox->addWidget(mCloseButton);

    hbox->insertStretch(1, 500);
    hbox->setSpacing(0);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    mMaxNormal = false;

    connect(mCloseButton, SIGNAL( clicked() ), parent, SLOT(close() ) );
    connect(mMinimizeButton, SIGNAL( clicked() ), this, SLOT(showSmall() ) );
    connect(mMaximizeButton, SIGNAL( clicked() ), this, SLOT(showMaxRestore() ) );
}

void TitleBar::titleChanged()
{
    mLabel->setText(parentWidget()->windowTitle());
}
void TitleBar::showMaxRestore()
{
    if (mMaxNormal) {
        parentWidget()->showNormal();
        mMaxNormal = !mMaxNormal;
        mMaximizeButton->setIcon(mMaxPix);
    } else {
        parentWidget()->showMaximized();
        mMaxNormal = !mMaxNormal;
        mMaximizeButton->setIcon(mRestorePix);
    }
}

void TitleBar::enterEvent(QEvent* e)
{
    setCursor(Qt::ArrowCursor);
    QWidget::enterEvent(e);
}

void TitleBar::mousePressEvent(QMouseEvent *me)
{
    if (me->button() == Qt::LeftButton) {
        mStartPos = me->globalPos();
        mClickPos = mapToParent(me->pos());
    }

    QWidget::mousePressEvent(me);
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *me)
{
    if (me->button() == Qt::LeftButton) {
        showMaxRestore();
    }

    QWidget::mouseDoubleClickEvent(me);
}

void TitleBar::mouseMoveEvent(QMouseEvent *me)
{
    if (mMaxNormal) {
        return QWidget::mouseMoveEvent(me);
    }
    parentWidget()->move(me->globalPos() - mClickPos);
}
