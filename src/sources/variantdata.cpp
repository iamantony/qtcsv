#include "include/variantdata.h"

using namespace QtCSV;

// Add empty row
void VariantData::addEmptyRow()
{
	m_values.append(QList<QVariant>());
}

// Add new row with one value
// @input:
// - value - value that should be written to the new row. If it is empty,
// it will be interpreted as empty line
// NOTE: value must be converted to a QString
// @output:
// - bool - True if new row with value was added, else False
bool VariantData::addRow(const QVariant& value)
{
	if ( value.canConvert<QString>() )
	{
		m_values.append( QList<QVariant>({value}) );
		return true;
	}

	return false;
}

// Add new row with list of values
// @input:
// - values - list of values. If list is empty, it will be interpreted
// as empty line
// NOTE: values must be converted to a QString
// @output:
// - bool - True if new row with values was added, else False
bool VariantData::addRow(const QList<QVariant> &values)
{
	for ( int i = 0; i < values.size(); ++i )
	{
		if ( false == values.at(i).canConvert<QString>() )
		{
			return false;
		}
	}

	m_values.append(values);

	return true;
}

// Add new row with values as strings
// @input:
// - values - list of strings. If list is empty, it will be interpreted
// as empty line
void VariantData::addRowValues(const QStringList &values)
{
	QList<QVariant> rowValues;
	for ( const QString &val : values )
	{
		rowValues.append(QVariant(val));
	}

	m_values.append(rowValues);
}

// Clear all data
void VariantData::clear()
{
	m_values.clear();
}

// Get number of rows
// @output:
// - int - current number of rows
int VariantData::getNumberOfRows() const
{
	return m_values.size();
}

// Get values (as strings) of specified row
// @input:
// - row - valid number of row
// @output:
// - QStringList - values of row. If row have invalid value, function will
// return empty QStringList.
QStringList VariantData::getRowValues(const int &row) const
{
	if ( row < 0 || getNumberOfRows() <= row )
	{
		return QStringList();
	}

	QStringList values;
	for ( int i = 0; i < m_values.at(row).size(); ++i )
	{
		values.append( m_values.at(row).at(i).toString() );
	}

	return values;
}

// Check if there are any data
// @output:
// - bool - True if there are some data (headlines or values), else False
bool VariantData::isEmpty() const
{

	return m_values.isEmpty();
}
