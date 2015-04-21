#include "H264NALListModel.h"
#include <QFile>

H264NALListModel::H264NALListModel(const QString &filename, QObject *parent)
    :QAbstractListModel(parent),
      m_filename(filename),
      m_fileBuffer(),
      m_nalList()
{
    load();
    parse();
}

void H264NALListModel::load()
{
    QFile file(m_filename);
    if (file.open(QFile::ReadOnly))
    {
        m_fileBuffer = file.readAll();
        file.close();
    }
}

void H264NALListModel::parse()
{
    int offset = 0;
    while(offset < m_fileBuffer.size())
    {
        int nal_start = 0;
        int nal_end = 0;
        find_nal_unit((uint8_t*)(m_fileBuffer.data() + offset), m_fileBuffer.size(), &nal_start, &nal_end);

        if (nal_end - nal_start > 0)
        {
            h264_stream_t *h = h264_new();
            read_nal_unit(h, &(((uint8_t*)m_fileBuffer.data())[nal_start + offset]), nal_end - nal_start);
            //debug_nal(h, h->nal);
            m_nalList.push_back(h);
        }

        offset += nal_end;
    }
}

int H264NALListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_nalList.size();
}

QVariant H264NALListModel::data(const QModelIndex &index, int role) const
{
    switch(role)
    {
    case Qt::DisplayRole:
    {
        h264_stream_t *h = m_nalList[index.row()];

        switch(h->nal->nal_unit_type)
        {
        case NAL_UNIT_TYPE_UNSPECIFIED:
            return QString("Unspecified");
        case NAL_UNIT_TYPE_CODED_SLICE_NON_IDR:
            return QString("Coded slice of a non-IDR picture");
        case NAL_UNIT_TYPE_CODED_SLICE_DATA_PARTITION_A:
            return QString("Coded slice data partition A");
        case NAL_UNIT_TYPE_CODED_SLICE_DATA_PARTITION_B:
            return QString("Coded slice data partition B");
        case NAL_UNIT_TYPE_CODED_SLICE_DATA_PARTITION_C:
            return QString("Coded slice data partition C");
        case NAL_UNIT_TYPE_CODED_SLICE_IDR:
            return QString("Coded slice of an IDR picture");
        case NAL_UNIT_TYPE_SEI:
            return QString("Supplemental enhancement information (SEI)");
        case NAL_UNIT_TYPE_SPS:
            return QString("Sequence parameter set");
        case NAL_UNIT_TYPE_PPS:
            return QString("Picture parameter set");
        case NAL_UNIT_TYPE_AUD:
            return QString("Access unit delimiter");
        case NAL_UNIT_TYPE_END_OF_SEQUENCE:
            return QString("End of sequence");
        case NAL_UNIT_TYPE_END_OF_STREAM:
            return QString("End of stream");
        case NAL_UNIT_TYPE_FILLER:
            return QString("Filler data");
        case NAL_UNIT_TYPE_SPS_EXT:
            return QString("Sequence parameter set extension");
        case NAL_UNIT_TYPE_CODED_SLICE_AUX:
            return QString("Coded slice of an auxiliary coded picture without partitioning");
        default:
            return QString("Unknown unit type");
        }
    }
    default:
        return QVariant();
    }
}

H264NALListModel::~H264NALListModel()
{
    foreach(h264_stream_t *h, m_nalList)
    {
        h264_free(h);
    }
}

