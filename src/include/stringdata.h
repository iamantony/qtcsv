#ifndef STRINGDATA_H
#define STRINGDATA_H

#include <QList>
#include <QStringList>

#include "qtcsv_global.h"
#include "abstractdata.h"

namespace QtCSV
{
    // StringData is a simple container class. It implement interface of
    // AbstractData class. It use strings to store information. It doesn't
    // provide support for converting other types to strings, so it will be
    // your work.
    class QTCSVSHARED_EXPORT StringData : public AbstractData
    {
    public:
        explicit StringData() {}
        virtual ~StringData() {}

        // Add new empty row
        virtual void addEmptyRow();
        // Add new row with specified values (as strings)
        virtual void addRow(const QStringList &values);
        // Clear all data
        virtual void clear();
        // Get number of rows
        virtual int getNumberOfRows() const;
        // Get values (as list of strings) of specified row
        virtual QStringList getRowValues(const int &row) const;
        // Check if there are any data
        virtual bool isEmpty() const;

    private:
        // Container for class data
        QList<QStringList> m_values;
    };
}

#endif // STRINGDATA_H
