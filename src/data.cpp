#include <QDebug>

#include "data.h"

using namespace QtCSV;

// Set headlines for the csv data
// @input:
// - headlines - list of headlines for table in csv file
void Data::setHeadlines(const QStringList &headlines)
{
	m_headlines = headlines;
}

// Get list of headlines
// @output:
// - QStringList - list of headlines (could be empty)
QStringList Data::getHeadlines() const
{
	return m_headlines;
}

// Add row value
// @input:
// - value - value that should be written in one row. If it is empty,
// it will be interpreted as empty line
// NOTE: value must can be converted to QString!
// @output:
// - true - value added
// - false - failed to add value
bool Data::addRow(const QVariant& value)
{
	if ( false == value.canConvert<QString>() )
	{
		qDebug() << "AddRow(): Error - values can not be converted to string";
		return false;
	}

	m_values.append( QList<QVariant>({value}) );

	return true;
}

// Add row values
// @input:
// - values - list of some values. If list is empty, it will be interpreted
// as empty line
// NOTE: values must can be converted to QString!
// @output:
// - true - values added
// - false - failed to add such values
bool Data::addRow(const QList<QVariant> &values)
{
	for ( int i = 0; i < values.size(); ++i )
	{
		if ( false == values.at(i).canConvert<QString>() )
		{
			qDebug() <<
				"AddRow(): Error - not all values can be converted to strings";
			return false;
		}
	}

	m_values.append(values);

	return true;
}

// Add empty row
void Data::addEmptyRow()
{
	m_values.append(QList<QVariant>());
}

// Get values for specified row
// @input:
// - rowNum - valid number of row
// - list - list where values will be written
// @output:
// - false - failed to get values of such row
// - true - values of row transformed to strings and added to input list
bool Data::getRowValues(const int &rowNum, QStringList *list) const
{
	int rows = getRowNum();
	if ( (nullptr == list) ||
		 (rowNum < 0) ||
		 (rows <= rowNum) )
	{
		qDebug() << "GetRowValues(): Error - invalid row number";
		return false;
	}

	for ( int i = 0; i < m_values.at(rowNum).size(); ++i )
	{
		QString strValue = m_values.at(rowNum).at(i).toString();
		list->append(strValue);
	}

	return true;
}

// Get number of rows
// @output:
// - int - current number of rows
int Data::getRowNum() const
{
	return m_values.size();
}

// Check if there are any data
// @output:
// - true - object hasn't any data
// - false - object has some data
bool Data::isEmpty() const
{
	if ( (true == m_headlines.isEmpty()) && (true == m_values.isEmpty()) )
	{
		return true;
	}

	return false;
}
