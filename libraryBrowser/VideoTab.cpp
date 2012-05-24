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
  cmb_content_dimension->setCurrentIndex(cmb_content_dimension->findText(""));
  cmb_video_format->setCurrentIndex(cmb_video_format->findText(""));
  cmb_frame_rate_max->setCurrentIndex(cmb_frame_rate_max->findText(""));
  cmb_frame_rate_min->setCurrentIndex(cmb_frame_rate_min->findText(""));
  cmb_content_motion->setCurrentIndex(cmb_content_motion->findText(""));
  cmb_aspect_ratio->setCurrentIndex(cmb_aspect_ratio->findText(""));
  cmb_sampling->setCurrentIndex(cmb_sampling->findText(""));
  cmb_frame_rate_scan->setCurrentIndex(cmb_frame_rate_scan->findText(""));
  cmb_res_size->setCurrentIndex(cmb_res_size->findText(""));
  cmb_content_style->setCurrentIndex(cmb_content_style->findText(""));
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
  connect(cmb_content_dimension, SIGNAL(activated(const QString)), this, SLOT(on_dimenstion_change(QString)));
  connect(cmb_content_motion, SIGNAL(activated(const QString)), this, SLOT(on_motion_change(QString)));
  connect(cmb_content_style, SIGNAL(activated(const QString)), this, SLOT(on_style_change(QString)));
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
  QGridLayout *grid = new QGridLayout;
  grid->addWidget(codecGroup(), 0, 0);
  grid->addWidget(resolutionGroup(), 0, 1);
  grid->addWidget(frameRateGroup(), 1, 0);
  grid->addWidget(contentGroup(), 1, 1);
  grid->addWidget(otherGroup(), 2, 0);
  setLayout(grid);
  setWindowTitle(tr("Group"));
  resize(640, 480);
}

QGroupBox *VideoTab::codecGroup()
{
  QGroupBox *groupBox = new QGroupBox(tr("Video Codec"));
  QFormLayout *layout = new QFormLayout;

  cmb_video_format = new QComboBox;
  cmb_video_bitrate = new QComboBox;

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


  //content_dimension
  values = code_int->get_combo_vals("Video", "content_dimension");
  values.removeAll("");
  current_selected = cmb_content_dimension->currentText();
  cmb_content_dimension->clear();

  cmb_content_dimension->addItem("");

  for(int i = 0; i < values.size(); i++)
  {
    cmb_content_dimension->addItem(values[i]);
  }
  index = cmb_content_dimension->findText(current_selected);
  cmb_content_dimension->setCurrentIndex(index);


  //content_motion
  values = code_int->get_combo_vals("Video", "content_motion");
  values.removeAll("");
  current_selected = cmb_content_motion->currentText();
  cmb_content_motion->clear();

  cmb_content_motion->addItem("");

  for(int i = 0; i < values.size(); i++)
  {
    cmb_content_motion->addItem(values[i]);
  }
  index = cmb_content_motion->findText(current_selected);
  cmb_content_motion->setCurrentIndex(index);


  //content_style
  values = code_int->get_combo_vals("Video", "content_style");
  values.removeAll("");
  current_selected = cmb_content_style->currentText();
  cmb_content_style->clear();

  cmb_content_style->addItem("");

  for(int i = 0; i < values.size(); i++)
  {
    cmb_content_style->addItem(values[i]);
  }
  index = cmb_content_style->findText(current_selected);
  cmb_content_style->setCurrentIndex(index);


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

QGroupBox *VideoTab::resolutionGroup()
{
  QGroupBox *groupBox = new QGroupBox(tr("Resolution"));
  QFormLayout *layout = new QFormLayout;

  cmb_res_standard = new QComboBox();
  cmb_res_size = new QComboBox();

  layout->addRow(new QLabel(tr("Format:")), cmb_res_standard);
  layout->addRow(new QLabel(tr("Size:")), cmb_res_size);
  groupBox->setLayout(layout);

  return groupBox;
}

QGroupBox *VideoTab::frameRateGroup()
{
  QGroupBox *groupBox = new QGroupBox(tr("Frame Rate"));
  QFormLayout *layout = new QFormLayout;

  cmb_frame_rate_scan = new QComboBox();
  cmb_frame_rate_min = new QComboBox();
  cmb_frame_rate_max = new QComboBox();

  layout->addRow(new QLabel(tr("Scan:")), cmb_frame_rate_scan);
  layout->addRow(new QLabel(tr("Fps min:")), cmb_frame_rate_min);
  layout->addRow(new QLabel(tr("Fps max:")), cmb_frame_rate_max);
  groupBox->setLayout(layout);

  return groupBox;
}

QGroupBox *VideoTab::otherGroup()
{
  QGroupBox *groupBox = new QGroupBox();
  QFormLayout *layout = new QFormLayout;

  cmb_encryption = new QComboBox();
  cmb_color_matrix = new QComboBox();
  cmb_aspect_ratio = new QComboBox();
  cmb_sampling = new QComboBox();

  layout->addRow(new QLabel("Encryption:"), cmb_encryption);
  layout->addRow(new QLabel(tr("Aspect Ratio:")), cmb_aspect_ratio);
  layout->addRow(new QLabel(tr("Color Matrix:")), cmb_color_matrix);
  layout->addRow(new QLabel(tr("Sampling:")), cmb_sampling);
  groupBox->setLayout(layout);

  return groupBox;
}

QGroupBox *VideoTab::contentGroup()
{
  QGroupBox *groupBox = new QGroupBox(tr("Content"));
  QFormLayout *layout = new QFormLayout;

  cmb_content_motion = new QComboBox();
  cmb_content_style = new QComboBox();
  cmb_content_dimension = new QComboBox();

  layout->addRow(new QLabel(tr("Motion:")), cmb_content_motion);
  layout->addRow(new QLabel(tr("Style:")), cmb_content_style);
  layout->addRow(new QLabel(tr("Dimension:")), cmb_content_dimension);
  groupBox->setLayout(layout);

  return groupBox;
};

void VideoTab::on_aspect_change(QString value)
{
  emit comboChange("Video", "aspect_ratio", value);
}

void VideoTab::on_color_change(QString value)
{
  emit comboChange("Video", "color_matrix", value);
}

void VideoTab::on_dimenstion_change(QString value)
{
  emit comboChange("Video", "content_dimension", value);
}

void VideoTab::on_motion_change(QString value)
{
  emit comboChange("Video", "content_motion", value);
}

void VideoTab::on_style_change(QString value)
{
  emit comboChange("Video", "content_style", value);
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
