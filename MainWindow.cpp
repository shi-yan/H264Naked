#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_currentH264Model(NULL)
{
    ui->setupUi(this);
    connect(ui->openPushButton, SIGNAL(clicked()), this, SLOT(onOpenFile()));
    connect(ui->nalTableView, SIGNAL(clicked(QModelIndex)), this, SLOT(onNalTableItemClicked(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpenFile()
{
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Open H264 file"), ".", tr("H264 Files (*.h264 *.264)"));

    QFileInfo fileInfo(filename);

    ui->filePathLineEdit->setText(fileInfo.absoluteFilePath());

    H264NALListModel *oldModel = NULL;
    if (m_currentH264Model)
    {
        oldModel = m_currentH264Model;
    }

    m_currentH264Model = new H264NALListModel(filename, this);

    ui->nalTableView->setModel(m_currentH264Model);

    for (int c = 0; c < ui->nalTableView->horizontalHeader()->count(); ++c)
    {
        ui->nalTableView->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    }

    if (oldModel)
    {
        delete oldModel;
    }
}

void MainWindow::onNalTableItemClicked(QModelIndex index)
{
    qDebug() << index.row();
    if (m_currentH264Model)
    {
        qDebug() << m_currentH264Model->data(index, Qt::UserRole).toString();
    }
}
