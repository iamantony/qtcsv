#ifndef QTCSVDATA_H
#define QTCSVDATA_H

#include <QList>
#include <QVariant>

#include "abstractdata.h"
#include "qtcsv_global.h"

class QStringList;

namespace QtCSV
{
    // VariantData is a simple container class. It implement interface of
    // AbstractData class. It use QVariant to hold information, so data could be
    // of almost any type - integral, strings and so on. There is only one
    // limitation - QVariant must be convertible to string (because,
    // obviously, if we want to save information to CSV file, we would need to
    // convert it to plain-text form). So don't forget to see docs of QVariant
    // before you start use this class.
    class QTCSVSHARED_EXPORT VariantData : public AbstractData
    {
    public:
        explicit VariantData() {}
        virtual ~VariantData() {}

        // Add new empty row
        virtual void addEmptyRow();
        // Add new row with one value
        bool addRow(const QVariant& value);
        // Add new row with list of values
        bool addRow(const QList<QVariant> &values);
        // Add new row with specified values (as strings)
        virtual void addRow(const QStringList &values);
        // Clear all data
        virtual void clear();
        // Get number of rows
        virtual int getNumberOfRows() const;
        // Get values (as list of strings) of specified row
        virtual QStringList getRowValues(const int &row) const;
        // Check if there are any rows
        virtual bool isEmpty() const;

        friend bool operator==(const VariantData& left,
                               const VariantData& right)
        {
            return left.m_values == right.m_values;
        }

        friend bool operator!=(const VariantData& left,
                               const VariantData& right)
        {
            return !(left == right);
        }

        // Add new row that would contain one value
        VariantData& operator<<(const QVariant &value);
        // Add new row with specified values
        VariantData& operator<<(const QList<QVariant> &values);
        VariantData& operator<<(const QStringList &values);

    private:
        // Container for class data
        QList< QList<QVariant> > m_values;
    };
}

#endif // QTCSVDATA_H
