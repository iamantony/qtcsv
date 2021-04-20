#ifndef QTCSVSTRINGDATA_H
#define QTCSVSTRINGDATA_H

#include "qtcsv/abstractdata.h"
#include "qtcsv/qtcsv_global.h"
#include <QList>
#include <QString>

namespace QtCSV
{
    // StringData is a simple container class. It implements interface of
    // AbstractData class and uses strings to store information. Also it
    // provides basic functions for working with rows.
    class QTCSVSHARED_EXPORT StringData : public AbstractData
    {
        class StringDataPrivate;
        StringDataPrivate* d_ptr;

    public:
        explicit StringData();
        StringData(const StringData& other);
        StringData& operator=(const StringData& other);
        virtual ~StringData();

        // Add new empty row
        virtual void addEmptyRow();
        // Add new row with one value
        void addRow(const QString& value);
        // Add new row with specified values (as strings)
        virtual void addRow(const QList<QString>& values);
        // Clear all data
        virtual void clear();
        // Insert new row at index position 'row'
        void insertRow(const int& row, const QString& value);
        void insertRow(const int& row, const QList<QString>& values);

        // Check if there are any data
        virtual bool isEmpty() const;
        // Remove the row at index position 'row'
        void removeRow(const int& row);
        // Replace the row at index position 'row' with new row
        void replaceRow(const int& row, const QString& value);
        void replaceRow(const int& row, const QList<QString>& values);

        // Reserve space for 'size' rows
        void reserve(const int& size);
        // Get number of rows
        virtual int rowCount() const;
        // Get values (as list of strings) of specified row
        virtual QList<QString> rowValues(const int& row) const;

        // Add new row that would contain one value
        StringData& operator<<(const QString& value);
        // Add new row with specified values
        StringData& operator<<(const QList<QString>& values);

        bool operator==(const StringData& other) const;
        friend bool operator!=(const StringData& left, const StringData& right)
        {
            return !(left == right);
        }
    };
}

#endif // QTCSVSTRINGDATA_H
