#include "messagebox.h"
#include "ui_messagebox.h"

MessageBox::MessageBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageBox)
{
    ui->setupUi(this);
    this->mousePressed = false;
}

MessageBox::~MessageBox()
{
    delete ui;
}

void MessageBox::SetMessage(const QString &msg, int type)
{
    if (type == 0) {

    } else if (type == 1) {

    } else if (type == 2) {

    }
}

void MessageBox::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void MessageBox::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void MessageBox::mouseReleaseEvent(QMouseEvent *)
{
     mousePressed = false;
}
