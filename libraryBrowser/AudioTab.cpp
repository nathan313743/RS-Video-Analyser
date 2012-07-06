#include "AudioTab.h"

AudioTab::AudioTab(QWidget *parent, CodeInterface &codeInt) : QWidget(parent)
{
    code_int = &codeInt;
    createDisplay();
    populateBoxes();
    createActions();
    connect(parent, SIGNAL(repopulate_combos()), this , SLOT(on_repopulate()));
    connect(parent, SIGNAL(reset_fields()), this, SLOT(on_reset()));
}

void AudioTab::on_repopulate()
{
    populateBoxes();
}

void AudioTab::on_reset()
{
    cmb_audio_format->setCurrentIndex(cmb_audio_format->findText(""));
    cmb_audio_bitrate->setCurrentIndex(cmb_audio_bitrate->findText(""));
    cmb_channel->setCurrentIndex(cmb_channel->findText(""));
    cmb_content->setCurrentIndex(cmb_content->findText(""));
    cmb_encryption->setCurrentIndex(cmb_encryption->findText(""));
    cmb_language->setCurrentIndex(cmb_language->findText(""));
    cmb_sampling->setCurrentIndex(cmb_sampling->findText(""));
}

void AudioTab::createActions()
{
    connect(cmb_audio_format, SIGNAL(activated(const QString)), this, SLOT(on_format_change(QString)));
    connect(cmb_audio_bitrate, SIGNAL(activated(const QString)), this, SLOT(on_bitrate_change(QString)));
    connect(cmb_channel, SIGNAL(activated(const QString)), this, SLOT(on_channel_change(QString)));
    connect(cmb_content, SIGNAL(activated(const QString)), this, SLOT(on_content_change(QString)));
    connect(cmb_encryption, SIGNAL(activated(const QString)), this, SLOT(on_encryption_change(QString)));
    connect(cmb_language, SIGNAL(activated(const QString)), this, SLOT(on_language_change(QString)));
    connect(cmb_sampling, SIGNAL(activated(const QString)), this, SLOT(on_sampling_change(QString)));
}

void AudioTab::createDisplay()
{
    QGridLayout *grid = new QGridLayout;
    grid->addWidget(groupCodec(), 0, 0);
    grid->addWidget(groupOther(), 1 ,0);


    setLayout(grid);
    setWindowTitle(tr("Group"));
    resize(640, 480);
}

void AudioTab::populateBoxes()
{
    QStringList values;
    QString current_selected = "";
    int index = -1;


    //format
    values = code_int->get_combo_vals("Audio", "audio_format");
    current_selected = cmb_audio_format->currentText();
    cmb_audio_format->clear();
    if(values.contains(""))
    {
        values.removeAll("");
    }
    cmb_audio_format->addItem("");
    for(int i = 0; i < values.size(); i++)
    {
        cmb_audio_format->addItem(values[i]);
    }
    index = cmb_audio_format->findText(current_selected);
    cmb_audio_format->setCurrentIndex(index);


    //bitrate
    values = code_int->get_combo_vals("Audio", "audio_bitrate_Kb");
    current_selected = cmb_audio_bitrate->currentText();
    cmb_audio_bitrate->clear();
    if(values.contains(""))
    {
        values.removeAll("");

    }
    cmb_audio_bitrate->addItem("");
    for(int i = 0; i < values.size(); i++)
    {
        cmb_audio_bitrate->addItem(values[i]);
    }
    index = cmb_audio_bitrate->findText(current_selected);
    cmb_audio_bitrate->setCurrentIndex(index);


    //channel
    values = code_int->get_combo_vals("Audio", "channel");
    current_selected = cmb_channel->currentText();
    cmb_channel->clear();
    if(values.contains(""))
    {
        values.removeAll("");
    }
    cmb_channel->addItem("");
    for(int i = 0; i < values.size(); i++)
    {
        cmb_channel->addItem(values[i]);
    }
    index = cmb_channel->findText(current_selected);
    cmb_channel->setCurrentIndex(index);


    //content
    values = code_int->get_combo_vals("Audio", "content");
    current_selected = cmb_content->currentText();
    cmb_content->clear();
    if(values.contains(""))
    {
        values.removeAll("");

    }
    cmb_content->addItem("");
    for(int i = 0; i < values.size(); i++)
    {
        cmb_content->addItem(values[i]);
    }
    index = cmb_content->findText(current_selected);
    cmb_content->setCurrentIndex(index);

    //encryption
    values = code_int->get_combo_vals("Audio", "encryption");
    current_selected = cmb_encryption->currentText();
    cmb_encryption->clear();
    if(values.contains(""))
    {
        values.removeAll("");

    }
    cmb_encryption->addItem("");
    for(int i = 0; i < values.size(); i++)
    {
        cmb_encryption->addItem(values[i]);
    }
    index = cmb_encryption->findText(current_selected);
    cmb_encryption->setCurrentIndex(index);

    //language
    values = code_int->get_combo_vals("Audio", "language_code");
    current_selected = cmb_language->currentText();
    cmb_language->clear();
    if(values.contains(""))
    {
        values.removeAll("");

    }
    cmb_language->addItem("");
    for(int i = 0; i < values.size(); i++)
    {
        cmb_language->addItem(values[i]);
    }
    index = cmb_language->findText(current_selected);
    cmb_language->setCurrentIndex(index);

    //sampling
    values = code_int->get_combo_vals("Audio", "sampling");
    current_selected = cmb_sampling->currentText();
    cmb_sampling->clear();
    if(values.contains(""))
    {
        values.removeAll("");
    }
    cmb_sampling->addItem("");
    for(int i = 0; i < values.size(); i++)
    {
        cmb_sampling->addItem(values[i]);
    }
    index = cmb_sampling->findText(current_selected);
    cmb_sampling->setCurrentIndex(index);
}

QGroupBox *AudioTab::groupCodec()
{
    QGroupBox *groupBox = new QGroupBox(tr("Audio Codec"),this);
    QFormLayout *layout = new QFormLayout(this);

    cmb_audio_format = new QComboBox(this);
    cmb_audio_bitrate = new QComboBox(this);

    cmb_audio_format->adjustSize();
    cmb_audio_bitrate->adjustSize();
    cmb_audio_format->setMinimumWidth(100);
    cmb_audio_bitrate->setMinimumWidth(100);

    layout->addRow(new QLabel(tr("Format:")), cmb_audio_format); /*Adds row to layout*/
    layout->addRow(new QLabel(tr("Bit Rate:")), cmb_audio_bitrate);
    groupBox->setMaximumHeight(80);
    groupBox->setLayout(layout);

    return groupBox;
}

QGroupBox *AudioTab::groupOther()
{
    QGroupBox *groupBox = new QGroupBox(this);
    QFormLayout *layout = new QFormLayout(this);

    cmb_channel = new QComboBox(this);
    cmb_content = new QComboBox(this);
    cmb_encryption = new QComboBox(this);
    cmb_language = new QComboBox(this);
    cmb_sampling = new QComboBox(this);

    cmb_channel->adjustSize();
    cmb_content->adjustSize();
    cmb_encryption->adjustSize();
    cmb_language->adjustSize();
    cmb_sampling->adjustSize();

    cmb_channel->setMinimumWidth(100);
    cmb_content->setMinimumWidth(100);
    cmb_encryption->setMinimumWidth(100);
    cmb_language->setMinimumWidth(100);
    cmb_sampling->setMinimumWidth(100);

    layout->addRow(new QLabel("Channel:",this),  cmb_channel);
    layout->addRow(new QLabel("Content:",this), cmb_content);
    layout->addRow(new QLabel("Encryption:",this), cmb_encryption);
    layout->addRow(new QLabel("Language:",this), cmb_language);
    layout->addRow(new QLabel("Sampling:",this), cmb_sampling);
    groupBox->setLayout(layout);

    return groupBox;
}

void AudioTab::on_format_change(QString value)
{
    emit comboChange("Audio", "audio_format", value);
}

void AudioTab::on_bitrate_change(QString value)
{
    emit comboChange("Audio", "audio_bitrate_Kb", value);
}

void AudioTab::on_channel_change(QString value)
{
    emit comboChange("Audio", "channel", value);
}

void AudioTab::on_content_change(QString value)
{
    emit comboChange("Audio", "content", value);
}

void AudioTab::on_encryption_change(QString value)
{
    emit comboChange("Audio", "encryption", value);
}

void AudioTab::on_language_change(QString value)
{
    emit comboChange("Audio", "language_code", value);
}

void AudioTab::on_sampling_change(QString value)
{
    emit comboChange("Audio", "sampling", value);
}
