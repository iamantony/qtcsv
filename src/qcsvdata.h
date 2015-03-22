#ifndef QCSVDATA_H
#define QCSVDATA_H

#include <QList>
#include <QStringList>
#include <QVariant>

#include "qtcsv_global.h"

class QTCSVSHARED_EXPORT QCSVData
{
	// == METHODS ==
public:
	explicit QCSVData() {}
	// Set headlines for the csv data
	void SetHeadlines(const QStringList &t_titles);
	// Get list of headlines
	QStringList GetHeadlines() const;
	// Add row value
	bool AddRow(const QVariant& t_value);
	// Add row values
	bool AddRow(const QList<QVariant> &t_values);
	// Add empty row
	void AddEmptyRow();
	// Get values for specified row
	bool GetRowValues(const int &t_rowNum, QStringList *t_list) const;
	// Get number of rows
	int GetRowsNum() const;
	// Check if there are any data
	bool IsEmpty() const;

	// == DATA ==
private:
	// Titles of the columns of csv file
	QStringList m_headlines;
	// Data that csv file contain
	QList< QList<QVariant> > m_values;
};

#endif // QCSVDATA_H
