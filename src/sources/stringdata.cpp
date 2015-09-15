#include "include/stringdata.h"

using namespace QtCSV;

// Add new empty row
void StringData::addEmptyRow()
{
    m_values << QStringList();
}

// Add new row with one value
// @input:
// - value - value that is supposed to be written to the new row
void StringData::addRow(const QString& value)
{
    m_values << (QStringList() << value);
}

// Add new row with specified values (as strings)
// @input:
// - values - list of strings. If list is empty, it will be interpreted
// as empty line
void StringData::addRow(const QStringList& values)
{
    m_values << values;
}

// Clear all data
void StringData::clear()
{
    m_values.clear();
}

// Insert new row at index position 'row'.
// @input:
// - row - index of row. If 'row' is 0, the value will be set as first row.
// If 'row' is rowCount(), the value will be added as new last row.
// - value - value that is supposed to be written to the new row
void StringData::insertRow(const int& row, const QString& value)
{
    insertRow(row, (QStringList() << value));
}

// Insert new row at index position 'row'.
// @input:
// - row - index of row. If 'row' is 0, the values will be set as first row.
// If 'row' is rowCount(), the values will be added as new last row.
// - values - list of strings
void StringData::insertRow(const int& row, const QStringList& values)
{
    m_values.insert(row, values);
}

// Check if there are any rows
// @output:
// - bool - True if there are any rows, else False
bool StringData::isEmpty() const
{
    return m_values.isEmpty();
}

// Removes the row at index position 'row'.
// @input:
// - row - index of row to remove. 'row' must be a valid index position
// (i.e., 0 <= row < rowCount()). Otherwise function will do nothing.
void StringData::removeRow(const int& row)
{
    m_values.removeAt(row);
}

// Replaces the row at index position 'row' with new row.
// @input:
// - row - index of row that should be replaced. 'row' must be
// a valid index position (i.e., 0 <= row < rowCount()).
// - value - value that is supposed to be written instead of the 'old' values
void StringData::replaceRow(const int& row, const QString& value)
{
    replaceRow(row, (QStringList() << value));
}

// Replaces the row at index position 'row' with new row.
// @input:
// - row - index of row that should be replaced. 'row' must be
// a valid index position (i.e., 0 <= row < rowCount()).
// - values - list of strings that is supposed to be written instead of the
// 'old' values
void StringData::replaceRow(const int& row, const QStringList& values)
{
    m_values.replace(row, values);
}

// Reserve space for 'size' rows.
// @input:
// - size - number of rows to reserve in memory. If 'size' is smaller than the
// current number of rows, nothing will happen.
void StringData::reserve(const int& size)
{
    m_values.reserve(size);
}

// Get number of rows
// @output:
// - int - current number of rows
int StringData::rowCount() const
{
    return m_values.size();
}

// Get values (as list of strings) of specified row
// @input:
// - row - valid number of row
// @output:
// - QStringList - values of row. If row is invalid number, function will
// return empty QStringList.
QStringList StringData::rowValues(const int& row) const
{
    if ( row < 0 || rowCount() <= row )
    {
        return QStringList();
    }

    return m_values.at(row);
}

// Add new row that would contain one value
StringData& StringData::operator<<(const QString& value)
{
    this->addRow(value);
    return *this;
}

// Add new row with specified values
StringData& StringData::operator<<(const QStringList& values)
{
    this->addRow(values);
    return *this;
}
