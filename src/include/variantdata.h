#ifndef QTCSVDATA_H
#define QTCSVDATA_H

#include <QList>
#include <QStringList>
#include <QVariant>

#include "abstractdata.h"
#include "qtcsv_global.h"

namespace QtCSV
{
    class QTCSVSHARED_EXPORT VariantData : public AbstractData
    {
    public:
        explicit VariantData() {}
        virtual ~VariantData() {}

        // Add empty row
        virtual void addEmptyRow() override;
        // Add new row with one value
        bool addRow(const QVariant& value);
        // Add new row with list of values
        bool addRow(const QList<QVariant> &values);
        // Add new row with values as strings
        virtual void addRow(const QStringList &values) override;
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
        QList< QList<QVariant> > m_values;
    };
}

#endif // QTCSVDATA_H
