#include "cmlifeview.h"
#include "ui_cmlifeview.h"

#include <universe.h>
#include <functional>

using namespace cmlife;

CMLifeView::CMLifeView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMLifeView)
{
    ui->setupUi(this);
}

CMLifeView::~CMLifeView()
{
    delete ui;
}

typedef Universe<int> U;


void CMLifeView::createUniverse()
{
    U u;

    std::function<U(U)> leftGen = [](const U& iu) {
        return left(iu);
        };

    std::function<U(U)> rightGen = [](const U& iu) {
        return right(iu);
        };



}
