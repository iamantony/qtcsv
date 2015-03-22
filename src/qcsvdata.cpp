#include <QDebug>

#include "qcsvdata.h"

// Set headlines for the csv data
// @input:
// - t_titles - list of titles for table in csv file
void QCSVData::SetHeadlines(const QStringList &t_titles)
{
	m_headlines = t_titles;
}

// Get list of headlines
// @output:
// - QStringList - list of headlines (could be empty)
QStringList QCSVData::GetHeadlines() const
{
	return m_headlines;
}

// Add row value
// @input:
// - t_value - value that should be written in one row. If it is empty,
// it will be interpreted as empty line
// NOTE: value must can be converted to QString!
// @output:
// - true - value added
// - false - failed to add value
bool QCSVData::AddRow(const QVariant& t_value)
{
	if ( false == t_value.canConvert<QString>() )
	{
		qDebug() << "AddRow(): Error - values can not be converted to string";
		return false;
	}

	m_values.append( QList<QVariant>({t_value}) );

	return true;
}

// Add row values
// @input:
// - t_values - list of some values. If list is empty, it will be interpreted
// as empty line
// NOTE: values must can be converted to QString!
// @output:
// - true - values added
// - false - failed to add such values
bool QCSVData::AddRow(const QList<QVariant> &t_values)
{
	for ( int i = 0; i < t_values.size(); ++i )
	{
		if ( false == t_values.at(i).canConvert<QString>() )
		{
			qDebug() <<
				"AddRow(): Error - not all values can be converted to strings";
			return false;
		}
	}

	m_values.append(t_values);

	return true;
}

// Add empty row
void QCSVData::AddEmptyRow()
{
	m_values.append(QList<QVariant>());
}

// Get values for specified row
// @input:
// - t_rowNum - valid number of row
// - t_list - list where values will be written
// @output:
// - false - failed to get values of such row
// - true - values of row transformed to strings and added to input list
bool QCSVData::GetRowValues(const int &t_rowNum, QStringList *t_list) const
{
	int rows = GetRowsNum();
	if ( (nullptr == t_list) ||
		 (t_rowNum < 0) ||
		 (rows <= t_rowNum) )
	{
		qDebug() << "GetRowValues(): Error - invalid row number";
		return false;
	}

	for ( int i = 0; i < m_values.at(t_rowNum).size(); ++i )
	{
		QString strValue = m_values.at(t_rowNum).at(i).toString();
		t_list->append(strValue);
	}

	return true;
}

// Get number of rows
// @output:
// - int - current number of rows
int QCSVData::GetRowsNum() const
{
	return m_values.size();
}

// Check if there are any data
// @output:
// - true - object hasn't any data
// - false - object has some data
bool QCSVData::IsEmpty() const
{
	if ( (true == m_headlines.isEmpty()) && (true == m_values.isEmpty()) )
	{
		return true;
	}

	return false;
}
