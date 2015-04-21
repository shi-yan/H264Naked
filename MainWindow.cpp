#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_currentH264Model(NULL)
{
    ui->setupUi(this);
    connect(ui->openPushButton, SIGNAL(clicked()), this, SLOT(onOpenFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpenFile()
{
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Open H264 file"), ".", tr("H264 Files (*.h264 *.264)"));

    H264NALListModel *oldModel = NULL;
    if (m_currentH264Model)
    {
        oldModel = m_currentH264Model;
    }

    m_currentH264Model = new H264NALListModel(filename, this);

    ui->nalListView->setModel(m_currentH264Model);

    if (oldModel)
    {
        delete oldModel;
    }
}
