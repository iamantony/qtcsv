# qtcsv

[![Build Status](https://travis-ci.org/iamantony/qtcsv.svg?branch=master)](https://travis-ci.org/iamantony/qtcsv)

Author: [Antony Cherepanov][1]  
E-mail: antony.cherepanov@gmail.com

Small easy-to-use library for reading and writing [csv-files][2] in Qt.  
Tested on Ubuntu 12.04 with Qt 4.8 and higher.

## Quick Example
```cpp
#include <QStringList>
#include <QDir>
#include <QDebug>

#include "stringdata.h"
#include "variantdata.h"
#include "reader.h"
#include "writer.h"

int main()
{
    // prepare data that you want to save to csv-file
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
    for ( int i = 0; i < readData.size(); ++i )
    {
        qDebug() << readData.at(i).join(",");
    }

    return 0;
}
```

## Usage
There are three main classes: **[Reader][3]**, **[Writer][4]** and
**[AbstractData][5]**.

#### AbstractData
**AbstractData** class is a pure abstract class that provide interface for a
container class. Here is the code:

```cpp
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

As you can see, **AbstractData** declare virtual functions for adding new rows,
getting rows values, clearing all information and so on. Basic stuff.

If you have said *Pure Abstract Class*, you must also say *Implementation*.
Don't worry, we have some: **[StringData][6]** and **[VariantData][7]**.

**StringData** class have the same interface as **AbstractData** and stores
all data as strings. It's useful when information that you want to save
in csv-file represented as strings. So if you have several strings that
form elements of one row, put them in **QStringList** and use function
**StringData::addRow(QStringList&)** to add new row.

If instead of strings you have list of *raw* data - integers, floating point
values, strings or (almost) anything else (example: [1, 3.14, "check"]) -
and you don't want to manually transform it to strings, then you can use
**QVariant** magic with **VariantData** class. Put your values into
**QVariants** and use one of **VariantData::addRow()** overloaded functions.

#### Reader
Use **Reader** class to read csv-files. It's simple. It has only two funtions.
To read csv-file you can use one of them:

1. **QList\<QStringList\> Reader::readToList(QString &filePath, QString &separator)**  
This function as first argument require string with absolute path to existent
csv-file (example: "/home/user/my-file.csv") and as second parameter it
needs delimeter symbol, that separate elements in a row (by default it use
comma - ",").  
As a result function will return **QList\<QStringList\>** with
read content of the file. If you're lucky, it will not be empty and
size of the **QList** will be equal to number of rows in csv-file. Each
**QStringList** contains elements of the corresponding row, represented as
strings.

2. **bool Reader::readToData(QString &filePath, AbstractData &data, QString &separator)**  
Second function is a little more advanced and, I hope, little more useful.
First argument - string with absolute path to existent csv-file, third
argument - delimeter symbol. And in the middle - second argument - there
is reference to **AbstractData**-based class object. Function will save
content of the file in this object, using virtual function
**AbstractData::addRow(QStringList)**. If you pass to function object
of class **StringData** or **VariantData**, elements of csv-file will
be saved in them as strings.  
If you are not happy with this fact, you can create your own
**AbstractData**-based concrete class and implement function
**addRow(QStringList)** in a way you want it.  
For example, if you know, that each row of your csv-file contains 3 elements
(integer value, floating-point value and string), then in function
**addRow(QStringList)** you can convert first element of **QStringList**
to int, second - to double and save all three elements to some container
(or do with them whatever you want).

#### Writer
Use **Writer** class to write to csv-files. It's simpler than **Reader**. It has
only one function! Here it is:

```cpp
bool Writer::write(const QString &filePath,
                   const AbstractData &data,
                   const QString &separator,
                   const WriteMode &mode,
                   const QStringList &header,
                   const QStringList &footer)
```

1. filePath - string with absolute path to csv-file (new or existent);
2. data - object, that contains information that you want to write to csv-file.  
**Writer** internally will use **QStringList AbstractData::getRowValues(int)**
function to get row values;
3. separator - delimeter symbol (default symbol is comma - ",");
4. mode - write mode flag.  
If it set to **WriteMode::REWRITE** and csv-file exist, then csv-file will be
rewritten. If flag set to **WriteMode::APPEND** and csv-file exist, then new
information will be appended to the end of the file.
5. header - strings that will be written at the beginning of the file, separated
with defined separator;
6. footer - strings that will be written at the end of the file, separated
with defined separator.

## Requirements
Qt 4.8 and higher.  
It is highly possible, that library will be successfully built with older Qt
versions (4.7, 4.6, ...). If you would try it, please write me back the results!

## Build
```bash
cd /path/to/folder/with/qtcsv
qmake -r
make

# If you want to run tests
cp ./src/libqtcsv.so.1 ./tests
make check
```

## Examples
Lets create example Qt project, that will use qtcsv library. We suppose, that
you use Ubuntu 12.04 and already have installed Qt Framework) with QtCreator
and read [Requirements](#requirements) section.

1. Open QtCreator and create new subdirs project (File -> New file or Project
-> Other Project -> Subdirs Project) with name MyProject.
2. Enter settings of our new project and clear flag *Shadow build*.
3. Add new console subproject to MyProject. Call it MyApp.
4. Clone repository of qtcsv library into MyProject folder. Via console:

    ```bash
    cd /path/to/MyProject
    git clone https://github.com/iamantony/qtcsv.git
    ```
So the structure of folder MyProject will be like this:
    ```
    /MyProject
    - /MyApp
    - /qtcsv
    - MyProject.pro
    ```

5. Edit MyProject.pro:

    ```qmake
    TEMPLATE = subdirs

    SUBDIRS += \
        qtcsv \
        MyApp
    ```

6. Edit MyApp.pro

    ```qmake
    QT += core
    QT -= gui

    TARGET = MyApp
    CONFIG += console
    CONFIG -= app_bundle

    TEMPLATE = app

    INCLUDEPATH += ../qtcsv/src/include
    LIBS += -lqtcsv

    unix {
        LIBS += -L../qtcsv/src
    }

    SOURCES += main.cpp
    ```

7. Edit /MyProject/MyApp/main.cpp

    ```cpp
    #include <QVariant>
    #include <QList>
    #include <QStringList>
    #include <QDir>
    #include <QDebug>

    #include "variantdata.h"
    #include "reader.h"
    #include "writer.h"

    int main()
    {
        QVariant first(2);

        QList<QVariant> second;
        second << QVariant("pi") << 3.14159265359;

        QStringList fourth;
        fourth << "one" << "two";

        QtCSV::VariantData varData;
        varData.addRow(first);
        varData.addRow(second);
        varData.addEmptyRow();
        varData.addRow(fourth);

        QString filePath = QDir::currentPath() + "/info.csv";
        if ( false == QtCSV::Writer::write(filePath, varData) )
        {
            qDebug() << "Failed to write to a file";
            return 1;
        }

        QList<QStringList> readData = QtCSV::Reader::readToList(filePath);
        for ( int i = 0; i < readData.size(); ++i )
        {
            qDebug() << readData.at(i).join(",");
        }

        return 0;
    }
    ```

8. Build and run. In console you'll see content of the created csv-file.

## Tags
c++, qt, qt4, qt5, csv, file

[1]: https://github.com/iamantony
[2]: http://en.wikipedia.org/wiki/Comma-separated_values
[3]: https://github.com/iamantony/qtcsv/blob/master/src/include/reader.h
[4]: https://github.com/iamantony/qtcsv/blob/master/src/include/writer.h
[5]: https://github.com/iamantony/qtcsv/blob/master/src/include/abstractdata.h
[6]: https://github.com/iamantony/qtcsv/blob/master/src/include/stringdata.h
[7]: https://github.com/iamantony/qtcsv/blob/master/src/include/variantdata.h
