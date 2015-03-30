#ifndef QTCSVDATA_H
#define QTCSVDATA_H

#include <QList>
#include <QStringList>
#include <QVariant>

#include "abstractdata.h"
#include "qtcsv_global.h"

namespace QtCSV
{
	class QTCSVSHARED_EXPORT VariantData : public AbstractData
	{
	public:
		explicit VariantData() {}
		virtual ~VariantData() {}

		// Add empty row
		virtual void addEmptyRow();
		// Add new row with one value
		bool addRow(const QVariant& value);
		// Add new row with list of values
		bool addRow(const QList<QVariant> &values);
		// Add new row with values as strings
		virtual void addRowValues(const QStringList &values);
		// Get list of headlines
		QStringList getHeadlines() const;
		// Get number of rows
		virtual int getNumberOfRows() const;
		// Get values (as strings) of specified row
		virtual QStringList getRowValues(const int &row) const;
		// Check if there are any data
		virtual bool isEmpty() const;
		// Set headlines for the data
		void setHeadlines(const QStringList &headlines);

	private:
		// Titles of the columns of csv file
		QStringList m_headlines;
		// Data that could be written to csv file
		QList<QList<QVariant>> m_values;
	};
}

#endif // QTCSVDATA_H
