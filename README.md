# qtcsv

[![Build Status](https://travis-ci.org/iamantony/qtcsv.svg?branch=master)](https://travis-ci.org/iamantony/qtcsv)

Small easy-to-use library for reading and writing [csv-files][1] in Qt.  
Tested under Ubuntu 12.04 with Qt 4.8 and higher.

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

#### AbstractData
**AbstractData** class is a pure abstract class that provide interface for
container class. It may sound scary, but in fact it just declare some function
names, that derived (concrete) class have to implement.

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

As you can see, there are methods for adding new rows, getting rows values,
clearing all information and so on. Basic stuff that helps you to store
information.

If you have said *Pure Abstract Class*, you must also say *Implementation*.
And we have some: **[StringData][5]** and **[VariantData][6]**.

**StringData** class have the same interface as **AbstractData** and stores
all data as strings. It's useful when all information that you want to save
in csv-file is already presented as strings. In this case use function
**StringData::addRow(QStringList&)**.

If you have *raw* data - list of integers, floating point values, strings that
you want to save in one row (like this: [1, 3.14, "check"]) - and you don't
want to manually transform it to strings, then you can use **QVariant** magic
with **VariantData** class. Put your values into **QVariants** and use
one of **VariantData::addRow()** overloaded functions.

#### Reader
Use **Reader** class to read csv-files. It's simple. It has only two funtions
and to read csv-file you can use one of them:

1. **QList\<QStringList\> Reader::readToList(QString &filePath, QString &separator)**  
This function as first argument require string with absolute path to existent
csv-file (example: "/home/user/my-file.csv") and as second parameter it
needs delimeter symbol, that separate elements in a row (by default it use
comma - ","). As a result function will return **QList\<QStringList\>** with
read content of the file. If you're lucky, it will not be empty and
size of the **QList** will be equal to number of rows in csv-file. Each
**QStringList** contains elements of the corresponding row, represented as
strings.

2. **bool Reader::readToData(QString &filePath, AbstractData &data, QString &separator)**
Second function is a little more advenced and I hope little more useful.
First argument - string with absolute path to existent csv-file, third
argument - delimeter symbol. And in the middle - second argument - there
is reference to **AbstractData**-based class object. Function will save
content of the file in this object, using virtual function 
**AbstractData::addRow(QStringList)**. If you pass to function object
of class **StringData** or **VariantData**, elements of csv-file will
be saved in them as strings.  
If you are not happy with this fact, you can create your own
**AbstractData**-based concrete class and implement function
**addRow(QStringList)** in a way you want.  
For example, if you know, that each row of your csv-file contains 3 elements
(integer value, floating-point value and string), then in function
**addRow(QStringList)** you can convert first element of **QStringList**
to int, second - to double and save all three elements to some container
(or do with them whatever you want).

#### Writer
Use **Writer** class to write to csv-files. It's simpler than **Reader**. It has
only one function! Here it is:

```cpp
bool Writer::write(QString &filePath, 
                   AbstractData &data,
                   QString &separator,
                   Writer::WriteMode &mode,
                   QStringList &header,
                   QStringList &footer)
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
Because **qtcsv** library uses C++11 features, you have to use compiler that
provide support for C++11. If you use **gcc** compiler, be sure that it's
version >= 4.7.

#### Install gcc-4.7 in Ubuntu 12.04
```bash
    # Add new repository
    sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
    sudo apt-get update
    
    # Install gcc-4.7 and g++-4.7 packages
    sudo apt-get install gcc-4.7 g++-4.7
    
    # Set up gcc-4.7 as default compiler
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.6 60 --slave /usr/bin/g++ g++ /usr/bin/g++-4.6
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.7 100 --slave /usr/bin/g++ g++ /usr/bin/g++-4.7
    
    # Check g++ version
    g++ --version
```

## Build
```bash
# Suppose we are in /qtcsv folder
qmake -r
make

# If you want to run tests
cp ./src/libqtcsv.so.1 ./tests
make check
```

## Examples
Lets create example Qt project, that will use qtcsv library. We suppose, that
you use Ubuntu 12.04 and already have installed Qt Framework (version 4.8 or
higher) with QtCreator and read [Requirements](#requirements) section of this
Readme file.

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

    ```
    TEMPLATE = subdirs
    
    SUBDIRS += \
        qtcsv \
        MyApp
    ```

6. Edit MyApp.pro

    ```
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
    
    equals(QT_MAJOR_VERSION, 4):equals(QT_MINOR_VERSION, 8) {
        QMAKE_CXXFLAGS += -std=c++0x
    }
    
    greaterThan(QT_MAJOR_VERSION, 4) {
        CONFIG += c++11
    }
    
    SOURCES += main.cpp
    ```

7. Edit /MyProject/MyApp/main.cpp
 
    ```
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
        for ( QStringList &list : readData )
        {
            qDebug() << list.join(",");
        }
    
        return 0;
    }
    ```
    
8. Build and run. In console you'll see content of the created csv-file.

## Tags
qt, qt4, qt5, csv, csv-file, read, write

[1]: http://en.wikipedia.org/wiki/Comma-separated_values
[2]: https://github.com/iamantony/qtcsv/blob/master/src/include/reader.h
[3]: https://github.com/iamantony/qtcsv/blob/master/src/include/writer.h
[4]: https://github.com/iamantony/qtcsv/blob/master/src/include/abstractdata.h
[5]: https://github.com/iamantony/qtcsv/blob/master/src/include/stringdata.h
[6]: https://github.com/iamantony/qtcsv/blob/master/src/include/variantdata.h
