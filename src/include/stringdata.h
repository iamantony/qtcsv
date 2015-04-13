#ifndef STRINGDATA_H
#define STRINGDATA_H

#include <QList>
#include <QStringList>

#include "qtcsv_global.h"
#include "abstractdata.h"

namespace QtCSV
{
	class QTCSVSHARED_EXPORT StringData : public AbstractData
	{
	public:
		explicit StringData() {}
		virtual ~StringData() {}

		// Add empty row
		virtual void addEmptyRow();
		// Add new row with values as strings
		virtual void addRowValues(const QStringList &values);
		// Clear all data
		virtual void clear();
		// Get number of rows
		virtual int getNumberOfRows() const;
		// Get values (as strings) of specified row
		virtual QStringList getRowValues(const int &row) const;
		// Check if there are any data
		virtual bool isEmpty() const;

	private:
		QList<QStringList> m_values;
	};
}

#endif // STRINGDATA_H
