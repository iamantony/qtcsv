#ifndef QTCSVDATA_H
#define QTCSVDATA_H

#include <QList>
#include <QStringList>
#include <QVariant>

#include "abstractdata.h"
#include "qtcsv_global.h"

namespace QtCSV
{
    // VariantData is a simple container class that uses interface provided
    // be AbstractData. It uses QVariant to hold information, so it could be
    // almost of any type - integral, strings and so on. There is only one
    // limitation - QVariant must be convertible to string (because,
    // obviously, if we want to save information to CSV file, we would need to
    // convert it to plain-text form). So don't forget to see docs of QVariant
    // before usage of this class.
    class QTCSVSHARED_EXPORT VariantData : public AbstractData
    {
    public:
        explicit VariantData() {}
        virtual ~VariantData() {}

        // Add new empty row
        virtual void addEmptyRow() override;
        // Add new row with one value
        bool addRow(const QVariant& value);
        // Add new row with list of values
        bool addRow(const QList<QVariant> &values);
        // Add new row with specified values (as strings)
        virtual void addRow(const QStringList &values) override;
        // Clear all data
        virtual void clear() override;
        // Get number of rows
        virtual int getNumberOfRows() const override;
        // Get values (as list of strings) of specified row
        virtual QStringList getRowValues(const int &row) const override;
        // Check if there are any rows
        virtual bool isEmpty() const override;

    private:
        // Container for class data
        QList< QList<QVariant> > m_values;
    };
}

#endif // QTCSVDATA_H
