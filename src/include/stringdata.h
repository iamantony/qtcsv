#ifndef STRINGDATA_H
#define STRINGDATA_H

#include <QList>
#include <QStringList>

#include "qtcsv_global.h"
#include "abstractdata.h"

namespace QtCSV
{
    // StringData is a simple container class. It implements interface of
    // AbstractData class and uses strings to store information.
    class QTCSVSHARED_EXPORT StringData : public AbstractData
    {
    public:
        explicit StringData() {}
        virtual ~StringData() {}

        // Add new empty row
        virtual void addEmptyRow();
        // Add new row with one value
        void addRow(const QString& value);
        // Add new row with specified values (as strings)
        virtual void addRow(const QStringList& values);
        // Clear all data
        virtual void clear();
        // Insert new row at index position 'row'
        void insertRow(const int& row, const QString& value);
        void insertRow(const int& row, const QStringList& values);
        // Check if there are any data
        virtual bool isEmpty() const;
        // Removes the row at index position 'row'
        void removeRow(const int& row);
        // Replaces the row at index position 'row' with new row
        void replaceRow(const int& row, const QString& value);
        void replaceRow(const int& row, const QStringList& values);
        // Reserve space for 'size' rows
        void reserve(const int& size);
        // Get number of rows
        virtual int rowCount() const;
        // Get values (as list of strings) of specified row
        virtual QStringList rowValues(const int& row) const;

        friend bool operator==(const StringData& left, const StringData& right)
        {
            return left.m_values == right.m_values;
        }

        friend bool operator!=(const StringData& left, const StringData& right)
        {
            return !(left == right);
        }

        // Add new row that would contain one value
        StringData& operator<<(const QString& value);
        // Add new row with specified values
        StringData& operator<<(const QStringList& values);

    private:
        // Container for class data
        QList<QStringList> m_values;
    };
}

#endif // STRINGDATA_H
