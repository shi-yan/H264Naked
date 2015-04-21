#ifndef H264NALLISTMODEL_H
#define H264NALLISTMODEL_H

#include <QAbstractTableModel>
#include <QByteArray>
#include <h264_stream.h>
#include <QVector>

class H264NALListModel : public QAbstractTableModel
{
    Q_OBJECT

    QString m_filename;
    QByteArray m_fileBuffer;
    QVector<h264_stream_t*> m_nalList;

public:
    H264NALListModel(const QString &filename, QObject *parent = NULL);
    ~H264NALListModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    void load();
    void parse();
};

#endif // H264NALLISTMODEL_H
