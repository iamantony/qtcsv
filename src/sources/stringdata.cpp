#include "include/stringdata.h"

using namespace QtCSV;

// Add new empty row
void StringData::addEmptyRow()
{
    m_values << QStringList();
}

// Add new row with one value
void StringData::addRow(const QString &value)
{
    m_values << (QStringList() << value);
}

// Add new row with specified values (as strings)
// @input:
// - values - list of strings. If list is empty, it will be interpreted
// as empty line
void StringData::addRow(const QStringList &values)
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

// Get values (as list of strings) of specified row
// @input:
// - row - valid number of row
// @output:
// - QStringList - values of row. If row is invalid number, function will
// return empty QStringList.
QStringList StringData::getRowValues(const int &row) const
{
    if ( row < 0 || getNumberOfRows() <= row )
    {
        return QStringList();
    }

    return m_values.at(row);
}

// Check if there are any rows
// @output:
// - bool - True if there are any rows, else False
bool StringData::isEmpty() const
{
    return m_values.isEmpty();
}

// Add new row that would contain one value
StringData& StringData::operator<<(const QString &value)
{
    this->addRow(value);
    return *this;
}

// Add new row with specified values
StringData& StringData::operator<<(const QStringList &values)
{
    this->addRow(values);
    return *this;
}
