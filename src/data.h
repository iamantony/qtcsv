#ifndef QTCSVDATA_H
#define QTCSVDATA_H

#include <QList>
#include <QStringList>
#include <QVariant>

#include "qtcsv_global.h"

namespace QtCSV
{
	class QTCSVSHARED_EXPORT Data
	{
	public:
		explicit Data() {}

		// Add empty row
		void addEmptyRow();
		// Add row value
		bool addRow(const QVariant& value);
		// Add row values
		bool addRow(const QList<QVariant> &values);
		// Get list of headlines
		QStringList getHeadlines() const;
		// Get number of rows
		int getRowNum() const;
		// Get values for specified row
		bool getRowValues(const int &rowNum, QStringList *list) const;
		// Check if there are any data
		bool isEmpty() const;
		// Set headlines for the csv data
		void setHeadlines(const QStringList &headlines);

	private:
		// Titles of the columns of csv file
		QStringList m_headlines;
		// Data that csv file contain
		QList<QList<QVariant>> m_values;
	};
}

#endif // QTCSVDATA_H
