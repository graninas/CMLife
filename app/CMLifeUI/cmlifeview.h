#ifndef CMLIFEVIEW_H
#define CMLIFEVIEW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QTimer>
#include <mutex>

namespace Ui {
class CMLifeView;
}

class CMLifeView : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMLifeView(QWidget *parent = 0);
    ~CMLifeView();

public slots:

    void createUniverse();

private:
    Ui::CMLifeView *ui;
};

#endif // CMLIFEVIEW_H
