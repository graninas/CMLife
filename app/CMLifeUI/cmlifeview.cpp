#include "cmlifeview.h"
#include "ui_cmlifeview.h"

#include <universe.h>
#include <functional>

#include <QDebug>

using namespace cmlife;

CMLifeView::CMLifeView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMLifeView)
{
    ui->setupUi(this);

    createUniverse();
}

CMLifeView::~CMLifeView()
{
    delete ui;
}


void CMLifeView::createUniverse()
{

}
