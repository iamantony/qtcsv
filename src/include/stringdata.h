#ifndef STRINGDATA_H
#define STRINGDATA_H

#include <QList>
#include <QStringList>

#include "qtcsv_global.h"
#include "abstractdata.h"

namespace QtCSV
{
    class QTCSVSHARED_EXPORT StringData : public AbstractData
    {
    public:
        explicit StringData() {}
        virtual ~StringData() {}

        // Add empty row
        virtual void addEmptyRow() override;
        // Add new row with values as strings
        virtual void addRowValues(const QStringList &values) override;
        // Clear all data
        virtual void clear() override;
        // Get number of rows
        virtual int getNumberOfRows() const override;
        // Get values (as strings) of specified row
        virtual QStringList getRowValues(const int &row) const override;
        // Check if there are any data
        virtual bool isEmpty() const override;

    private:
        // Container for class data
        QList<QStringList> m_values;
    };
}

#endif // STRINGDATA_H
