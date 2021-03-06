#include "VideoTab.h"

VideoTab::VideoTab(QWidget *parent, CodeInterface &codeInt) : QWidget(parent)
{
    code_int = &codeInt;
    createDisplay();
    populateBoxes();
    createActions();
    connect(parent, SIGNAL(repopulate_combos()), this , SLOT(on_repopulate()));
    connect(parent, SIGNAL(reset_fields()), this, SLOT(on_reset()));
}


void VideoTab::on_reset()
{
    cmb_encryption->setCurrentIndex(cmb_encryption->findText(""));
    cmb_video_bitrate->setCurrentIndex(cmb_video_bitrate->findText(""));
    cmb_color_matrix->setCurrentIndex(cmb_color_matrix->findText(""));
    cmb_video_format->setCurrentIndex(cmb_video_format->findText(""));
    cmb_frame_rate_max->setCurrentIndex(cmb_frame_rate_max->findText(""));
    cmb_frame_rate_min->setCurrentIndex(cmb_frame_rate_min->findText(""));
    cmb_aspect_ratio->setCurrentIndex(cmb_aspect_ratio->findText(""));
    cmb_sampling->setCurrentIndex(cmb_sampling->findText(""));
    cmb_frame_rate_scan->setCurrentIndex(cmb_frame_rate_scan->findText(""));
    cmb_res_size->setCurrentIndex(cmb_res_size->findText(""));
    cmb_res_standard->setCurrentIndex(cmb_res_standard->findText(""));
}

void VideoTab::on_repopulate()
{
    populateBoxes();
}

void VideoTab::createActions()
{
    connect(cmb_aspect_ratio, SIGNAL(activated(const QString)), this, SLOT(on_aspect_change(QString)));
    connect(cmb_color_matrix, SIGNAL(activated(const QString)), this, SLOT(on_color_change(QString)));
    connect(cmb_encryption, SIGNAL(activated(const QString)), this, SLOT(on_encryption_change(QString)));
    connect(cmb_frame_rate_min, SIGNAL(activated(const QString)), this, SLOT(on_framerate_change_min(QString)));
    connect(cmb_frame_rate_max, SIGNAL(activated(const QString)), this, SLOT(on_framerate_change_max(QString)));
    connect(cmb_frame_rate_scan, SIGNAL(activated(const QString)), this, SLOT(on_scan_change(QString)));
    connect(cmb_res_size, SIGNAL(activated(const QString)), this, SLOT(on_resSize_change(QString)));
    connect(cmb_res_standard, SIGNAL(activated(const QString)), this, SLOT(on_resStandard_change(QString)));
    connect(cmb_sampling, SIGNAL(activated(const QString)), this, SLOT(on_sampling_change(QString)));
    connect(cmb_video_bitrate, SIGNAL(activated(const QString)), this, SLOT(on_vidBitrate_change(QString)));
    connect(cmb_video_format, SIGNAL(activated(const QString)), this, SLOT(on_vidFormat_change(QString)));
}

void VideoTab::createDisplay()
{
    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(groupCodec(), 0, 0);
    grid->addWidget(groupResolustion(), 0, 1);
    grid->addWidget(groupFrameRate(), 1, 0);
    grid->addWidget(groupOther(), 2, 0);
    setLayout(grid);
    setWindowTitle(tr("Group"));
    resize(640, 480);
}

QGroupBox *VideoTab::groupCodec()
{
    QGroupBox *groupBox = new QGroupBox(tr("Video Codec"),this);
    QFormLayout *layout = new QFormLayout(this);

    cmb_video_format = new QComboBox(this);
    cmb_video_bitrate = new QComboBox(this);

    cmb_video_format->adjustSize();
    cmb_video_bitrate->adjustSize();
    cmb_video_format->setMinimumWidth(100);
    cmb_video_bitrate->setMinimumWidth(100);

    layout->addRow(new QLabel(tr("Format:")), cmb_video_format);
    layout->addRow(new QLabel(tr("Bit Rate:")), cmb_video_bitrate);
    groupBox->setLayout(layout);

    return groupBox;
}



void VideoTab::populateBoxes()
{
    QStringList values;
    QString current_selected = "";
    int index = -1;

    //aspect_ratio
    values = code_int->get_combo_vals("Video", "aspect_ratio");
    values.removeAll("");
    current_selected = cmb_aspect_ratio->currentText();
    cmb_aspect_ratio->clear();

    cmb_aspect_ratio->addItem("");

    for(int i = 0; i < values.size(); i++)
    {
        cmb_aspect_ratio->addItem(values[i]);
    }
    index = cmb_aspect_ratio->findText(current_selected);
    cmb_aspect_ratio->setCurrentIndex(index);


    //color_matrix
    values = code_int->get_combo_vals("Video", "color_matrix");
    values.removeAll("");
    current_selected = cmb_color_matrix->currentText();
    cmb_color_matrix->clear();
    cmb_color_matrix->addItem("");

    for(int i = 0; i < values.size(); i++)
    {
        cmb_color_matrix->addItem(values[i]);
    }
    index = cmb_color_matrix->findText(current_selected);
    cmb_color_matrix->setCurrentIndex(index);


    //encryption
    values = code_int->get_combo_vals("Video", "encryption");
    values.removeAll("");
    current_selected = cmb_encryption->currentText();
    cmb_encryption->clear();

    cmb_encryption->addItem("");

    for(int i = 0; i < values.size(); i++)
    {
        cmb_encryption->addItem(values[i]);
    }
    index = cmb_encryption->findText(current_selected);
    cmb_encryption->setCurrentIndex(index);


    //frame_rate_scan
    values = code_int->get_combo_vals("Video", "frame_rate_scan");
    values.removeAll("");
    current_selected = cmb_frame_rate_scan->currentText();
    cmb_frame_rate_scan->clear();

    cmb_frame_rate_scan->addItem("");

    for(int i = 0; i < values.size(); i++)
    {
        cmb_frame_rate_scan->addItem(values[i]);
    }
    index = cmb_frame_rate_scan->findText(current_selected);
    cmb_frame_rate_scan->setCurrentIndex(index);


    //frame_rate_value_min
    values = code_int->get_combo_vals("Video", "frame_rate_value");
    values.removeAll("");
    current_selected = cmb_frame_rate_min->currentText();
    cmb_frame_rate_min->clear();

    cmb_frame_rate_min->addItem("");

    for(int i = 0; i < values.size(); i++)
    {
        cmb_frame_rate_min->addItem(values[i]);
    }
    index = cmb_frame_rate_min->findText(current_selected);
    cmb_frame_rate_min->setCurrentIndex(index);


    //frame_rate_value_max
    values = code_int->get_combo_vals("Video", "frame_rate_value");
    values.removeAll("");
    current_selected = cmb_frame_rate_max->currentText();
    cmb_frame_rate_max->clear();

    cmb_frame_rate_max->addItem("");

    for(int i = (values.size() - 1); i >= 0; i--)
    { //Reverses the order of the elements
        cmb_frame_rate_max->addItem(values[i]);
    }
    index = cmb_frame_rate_max->findText(current_selected);
    cmb_frame_rate_max->setCurrentIndex(index);


    //res_size
    values = code_int->get_combo_vals("Video", "res_size");
    values.removeAll("");
    current_selected = cmb_res_size->currentText();
    cmb_res_size->clear();

    cmb_res_size->addItem("");

    for(int i = 0; i < values.size(); i++)
    {
        cmb_res_size->addItem(values[i]);
    }
    index = cmb_res_size->findText(current_selected);
    cmb_res_size->setCurrentIndex(index);


    //res_standard
    values = code_int->get_combo_vals("Video", "res_standard");
    values.removeAll("");
    current_selected = cmb_res_standard->currentText();
    cmb_res_standard->clear();

    cmb_res_standard->addItem("");

    for(int i = 0; i < values.size(); i++)
    {
        cmb_res_standard->addItem(values[i]);
    }
    index = cmb_res_standard->findText(current_selected);
    cmb_res_standard->setCurrentIndex(index);


    //sampling
    values = code_int->get_combo_vals("Video", "sampling");
    values.removeAll("");
    current_selected = cmb_sampling->currentText();
    cmb_sampling->clear();

    cmb_sampling->addItem("");

    for(int i = 0; i < values.size(); i++)
    {
        cmb_sampling->addItem(values[i]);
    }
    index = cmb_sampling->findText(current_selected);
    cmb_sampling->setCurrentIndex(index);


    //video_bitrate_Kb
    values = code_int->get_combo_vals("Video", "video_bitrate_Kb");
    values.removeAll("");
    current_selected = cmb_video_bitrate->currentText();
    cmb_video_bitrate->clear();

    cmb_video_bitrate->addItem("");

    for(int i = 0; i < values.size(); i++)
    {
        cmb_video_bitrate->addItem(values[i]);
    }
    index = cmb_video_bitrate->findText(current_selected);
    cmb_video_bitrate->setCurrentIndex(index);


    //video_format
    values = code_int->get_combo_vals("Video", "video_format");
    values.removeAll("");
    current_selected = cmb_video_format->currentText();
    cmb_video_format->clear();

    cmb_video_format->addItem("");

    for(int i = 0; i < values.size(); i++)
    {
        cmb_video_format->addItem(values.at(i));
    }
    index = cmb_video_format->findText(current_selected);
    cmb_video_format->setCurrentIndex(index);

}

QGroupBox *VideoTab::groupResolustion()
{
    QGroupBox *groupBox = new QGroupBox(tr("Resolution"));
    QFormLayout *layout = new QFormLayout(this);

    cmb_res_standard = new QComboBox(this);
    cmb_res_size = new QComboBox(this);

    cmb_res_standard->adjustSize();
    cmb_res_size->adjustSize();
    cmb_res_standard->setMinimumWidth(100);
    cmb_res_size->setMinimumWidth(100);

    layout->addRow(new QLabel(tr("Format:")), cmb_res_standard);
    layout->addRow(new QLabel(tr("Size:")), cmb_res_size);
    groupBox->setLayout(layout);

    return groupBox;
}

QGroupBox *VideoTab::groupFrameRate()
{
    QGroupBox *groupBox = new QGroupBox(tr("Frame Rate"));
    QFormLayout *layout = new QFormLayout(this);

    cmb_frame_rate_scan = new QComboBox(this);
    cmb_frame_rate_min = new QComboBox(this);
    cmb_frame_rate_max = new QComboBox(this);

    cmb_frame_rate_scan->adjustSize();
    cmb_frame_rate_min->adjustSize();
    cmb_frame_rate_max->adjustSize();
    cmb_frame_rate_scan->setMinimumWidth(100);
    cmb_frame_rate_min->setMinimumWidth(100);
    cmb_frame_rate_max->setMinimumWidth(100);

    layout->addRow(new QLabel(tr("Scan:")), cmb_frame_rate_scan);
    layout->addRow(new QLabel(tr("Fps min:")), cmb_frame_rate_min);
    layout->addRow(new QLabel(tr("Fps max:")), cmb_frame_rate_max);
    groupBox->setLayout(layout);

    return groupBox;
}

QGroupBox *VideoTab::groupOther()
{
    QGroupBox *groupBox = new QGroupBox(this);
    QFormLayout *layout = new QFormLayout(this);

    cmb_encryption = new QComboBox(this);
    cmb_color_matrix = new QComboBox(this);
    cmb_aspect_ratio = new QComboBox(this);
    cmb_sampling = new QComboBox(this);


    cmb_encryption->adjustSize();
    cmb_color_matrix->adjustSize();
    cmb_aspect_ratio->adjustSize();
    cmb_sampling->adjustSize();
    cmb_encryption->setMinimumWidth(100);
    cmb_color_matrix->setMinimumWidth(100);
    cmb_aspect_ratio->setMinimumWidth(100);
    cmb_sampling->setMinimumWidth(100);

    layout->addRow(new QLabel("Encryption:"), cmb_encryption);
    layout->addRow(new QLabel(tr("Aspect Ratio:")), cmb_aspect_ratio);
    layout->addRow(new QLabel(tr("Color Matrix:")), cmb_color_matrix);
    layout->addRow(new QLabel(tr("Sampling:")), cmb_sampling);
    groupBox->setLayout(layout);

    return groupBox;
}

void VideoTab::on_aspect_change(QString value)
{
    emit comboChange("Video", "aspect_ratio", value);
}

void VideoTab::on_color_change(QString value)
{
    emit comboChange("Video", "color_matrix", value);
}

void VideoTab::on_encryption_change(QString value)
{
    emit comboChange("Video", "encryption", value);
}

void VideoTab::on_scan_change(QString value)
{
    emit comboChange("Video", "frame_rate_scan", value);
}

void VideoTab::on_framerate_change_min(QString value)
{
    emit comboChange("Video", "frame_rate_value_min", value);
}

void VideoTab::on_framerate_change_max(QString value)
{
    emit comboChange("Video", "frame_rate_value_max", value);
}

void VideoTab::on_resSize_change(QString value)
{
    emit comboChange("Video", "res_size", value);
}

void VideoTab::on_resStandard_change(QString value)
{
    emit comboChange("Video", "res_standard", value);
}

void VideoTab::on_sampling_change(QString value)
{
    emit comboChange("Video", "sampling", value);
}

void VideoTab::on_vidBitrate_change(QString value)
{
    emit comboChange("Video", "video_bitrate_Kb", value);
}

void VideoTab::on_vidFormat_change(QString value)
{
    emit comboChange("Video", "video_format", value);
}
