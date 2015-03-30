#include "stringdata.h"

using namespace QtCSV;

// Add empty row
void StringData::addEmptyRow()
{
	m_values << QStringList();
}

// Add new row with values as strings
// @input:
// - values - list of strings. If list is empty, it will be interpreted
// as empty line
void StringData::addRowValues(const QStringList &values)
{
	m_values << values;
}

// Clear all data
void StringData::clear()
{
	m_values.clear();
}

// Get number of rows
// @output:
// - int - current number of rows
int StringData::getNumberOfRows() const
{
	return m_values.size();
}

// Get values (as strings) of specified row
// @input:
// - row - valid number of row
// @output:
// - QStringList - values of row. If row have invalid value, function will
// return empty QStringList.
QStringList StringData::getRowValues(const int &row) const
{
	if ( row < 0 || getNumberOfRows() <= row )
	{
		return QStringList();
	}

	return m_values.at(row);
}

// Check if there are any data
// @output:
// - bool - True if there are some data, else False
bool StringData::isEmpty() const
{
	return m_values.isEmpty();
}
