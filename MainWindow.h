#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "H264NALListModel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    H264NALListModel *m_currentH264Model;

private slots:
    void onOpenFile();
};

#endif // MAINWINDOW_H
