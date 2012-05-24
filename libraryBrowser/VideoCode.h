#ifndef VideoCode_H_
#define VideoCode_H_
#include <QVector>
#include <QString>
#include <QWidget>
#include <QStringList>

/**
 * Used to hold the SQL WHERE clause.  Updated whenever the Tab is updated.
 */
class VideoCode : public QWidget{
	Q_OBJECT

public:
	VideoCode();

	QVector<QString> getFields();
	QStringList get_clauses();

	void updateValues(QString&, QString&);
	
	void reset();

	void set_aspect_ratio(QString &);
	void set_color_matrix(QString &);
	void set_content_dimension(QString &);
	void set_content_motion(QString &);
	void set_content_style(QString &);
	void set_encryption(QString &);
	void set_frame_rate_scan(QString &);
	void set_frame_rate_value_max(QString &);
	void set_frame_rate_value_min(QString &);
	void set_res_size(QString &);
	void set_res_standard(QString &);
	void set_sampling(QString &);
	void set_video_bitrate_kb(QString &);
	void set_video_format(QString &);
	

private:
	QStringList clause_list;

	void append_clauses();
	
	QString aspect_ratio_clause;
	QString color_matrix_clause;
	QString content_dimension_clause;
	QString content_motion_clause;
	QString content_style_clause;
	QString encryption_clause;
	QString frame_rate_scan_clause;
	QString frame_rate_value_max_clause;
	QString frame_rate_value_min_clause;
	QString res_size_clause;
	QString res_standard_clause;
	QString sampling_clause;
	QString video_bitrate_kb_clause;
	QString video_format_clause;

};
#endif /* VideoCode_H_ */
