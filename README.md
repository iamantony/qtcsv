# qtcsv

[![Build Status](https://travis-ci.org/iamantony/qtcsv.svg?branch=master)](https://travis-ci.org/iamantony/qtcsv)

Small easy-to-use library for reading and writing [csv-files][1] in Qt.  
Tested with Qt 4.8 and higher.

## Quick example

```
    #include <QStringList>
    #include <QDir>
    #include <QDebug>

    #include "stringdata.h"
    #include "variantdata.h"
    #include "reader.h"
    #include "writer.h"

    int main()
    {
        // prepare data to save to csv-file
        QStringList strList;
        strList << "one" << "two" << "three";

        QtCSV::StringData strData;
        strData.addRowValues(strList);
        strData.addEmptyRow();
        strData.addRowValues(strList);

        // write to file
        QString filePath = QDir::currentPath() + "/test.csv";
        QtCSV::Writer::write(filePath, strData);

        // read data from file
        QList<QStringList> readData = QtCSV::Reader::readToList(filePath);
        for ( QStringList &list : readData )
        {
            qDebug() << list.join(",");
        }

        return 0;
    }
```

## Usage

There are three main classes: **[Reader][2]**, **[Writer][3]** and
**[AbstractData][4]**.

**AbstractData** class is a pure abstract class that provide interface for
container class. It may sound scary, but in fact it just declare some function
names, that derived (concrete) class have to implement.

```
    class AbstractData
    {
    public:
        explicit AbstractData() {}
        virtual ~AbstractData() {}

        // Add new empty row
        virtual void addEmptyRow() = 0;
        // Add new row with specified values (as strings)
        virtual void addRow(const QStringList &values) = 0;
        // Clear all data
        virtual void clear() = 0;
        // Get number of rows
        virtual int getNumberOfRows() const = 0;
        // Get values (as list of strings) of specified row
        virtual QStringList getRowValues(const int &row) const = 0;
        // Check if there are any rows
        virtual bool isEmpty() const = 0;
    };
```

As you can see, there are methods for adding new rows, getting rows values,
clearing all information and so on. Basic stuff that helps you to store
information.

If you have said *Pure Abstract Class*, you must also say *Implementation*.
And we have some: **[StringData][5]**, **[VariantData][6]**.

**StringData** class have the same interface as **AbstractData** and stores
all data as strings. It's useful when all information that you want to store
in csv-file is already presented as strings. Just use function
**addRow(QStringList&)** and move on.

If you have *raw* data - list of integers, floating point values, strings that
you want to save in one row (like this: [1, 3.14, "check"]) - and you don't
want to manually transform it to strings, then you can use **QVariant** magic
with **VariantData** class. Put your values in to **QVariants** and use
one of **addRow()** overloaded functions of **VariantData**.

# Tags
qt, qt4, qt5, csv, csv-file, read, write

[1]: http://en.wikipedia.org/wiki/Comma-separated_values
[2]: https://github.com/iamantony/qtcsv/blob/master/src/include/reader.h
[3]: https://github.com/iamantony/qtcsv/blob/master/src/include/writer.h
[4]: https://github.com/iamantony/qtcsv/blob/master/src/include/abstractdata.h
[5]: https://github.com/iamantony/qtcsv/blob/master/src/include/stringdata.h
[6]: https://github.com/iamantony/qtcsv/blob/master/src/include/variantdata.h
