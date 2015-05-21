#include "include/variantdata.h"

using namespace QtCSV;

// Add new empty row
void VariantData::addEmptyRow()
{
    m_values << QList<QVariant>();
}

// Add new row with one value
// @input:
// - value - value that is supposed to be written to the new row.
// If value is empty, empty row will be added.
// NOTE: value must be convertable to a QString
// @output:
// - bool - True if new row was successfully added, else False
bool VariantData::addRow(const QVariant& value)
{
    if ( false == value.canConvert<QString>() )
    {
        return false;
    }

    QList<QVariant> rowValues;
    rowValues << value;

    m_values << rowValues;

    return true;
}

// Add new row with list of values
// @input:
// - values - list of values. If list is empty, empty row will be added.
// NOTE: values must be convertable to a QString
// @output:
// - bool - True if new row was successfully added, else False
bool VariantData::addRow(const QList<QVariant> &values)
{
    for ( QList<QVariant>::const_iterator iter = values.constBegin();
          iter != values.constEnd(); ++iter)
    {
        if ( false == (*iter).canConvert<QString>() )
        {
            return false;
        }
    }

    m_values << values;

    return true;
}

// Add new row with specified values (as strings)
// @input:
// - values - list of strings. If list is empty, empty row will be added.
void VariantData::addRow(const QStringList &values)
{
    QList<QVariant> rowValues;
    for ( QStringList::const_iterator iter = values.constBegin();
          iter != values.constEnd(); ++iter)
    {
        rowValues << QVariant(*iter);
    }

    m_values << rowValues;
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

// Get values (as list of strings) of specified row
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
        values << m_values.at(row).at(i).toString();
    }

    return values;
}

// Check if there are any rows
// @output:
// - bool - True if there are any rows, else False
bool VariantData::isEmpty() const
{

    return m_values.isEmpty();
}
