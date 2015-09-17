# qtcsv

[![Build Status](https://travis-ci.org/iamantony/qtcsv.svg?branch=master)](https://travis-ci.org/iamantony/qtcsv)

Author: [Antony Cherepanov][1]  
E-mail: antony.cherepanov@gmail.com

Small easy-to-use library for reading and writing [csv-files][2] in Qt.  
Tested on Ubuntu 12.04 with gcc 4.6.3, Qt 4.8 and higher.

## Quick Example
```cpp
#include <QList>
#include <QStringList>
#include <QDir>
#include <QDebug>

#include "stringdata.h"
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
    strData << strList << "this is the last row";

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
**AbstractData** is a pure abstract class that provide interface for a
container class. Here is how it looks:

```cpp
class QTCSVSHARED_EXPORT AbstractData
{
public:
    explicit AbstractData() {}
    virtual ~AbstractData() {}

    virtual void addEmptyRow() = 0;
    virtual void addRow(const QStringList& values) = 0;
    virtual void clear() = 0;
    virtual bool isEmpty() const = 0;
    virtual int rowCount() const = 0;
    virtual QStringList rowValues(const int& row) const = 0;
};
```

As you can see, **AbstractData** declare virtual functions for adding new rows,
getting rows values, clearing all information and so on. Basic stuff for a
container class.

If you have said *Pure Abstract Class*, you must also say *Implementation*.
Don't worry, we have some:

##### StringData
**[StringData][6]** have the same interface as **AbstractData** (plus some useful
functions for inserting rows, removing rows and so on) and stores
all data as strings. It's useful when information that you want to save
in csv-file is represented as strings.

##### VariantData
If you store information in different types - integers, floating point
values, strings or (almost) anything else (example: [1, 3.14, "check"]) -
and you don't want to manually transform each element to string, then you
can use **QVariant** magic. Wrap your data into **QVariants** and pass it to
**[VariantData][7]** class.

#### Reader
Use **Reader** class to read csv-files. It's simple. It has only two funtions:

1. **QList\<QStringList\> readToList(QString& filePath, QString& separator, QTextCodec* codec)**

  - *filePath* - string with absolute path to existent csv-file 
  (example: "/home/user/my-file.csv");  
  - *separator* (optional) - delimeter symbol, that separate elements 
  in a row (by default it is comma - ",");  
  - *codec* (optional) - pointer to the codec object that will be used 
  to read data from the file (by default it is codec for locale).  
    
  As a result function will return **QList\<QStringList\>** with
  that hold content of the file. If all went smooth, list will not be 
  empty and size of it will be equal to number of rows in csv-file. Each
  **QStringList** will contain elements of the corresponding row, 
  represented as strings.

2. **bool Reader::readToData(QString& filePath, AbstractData& data, QString& separator, QTextCodec* codec)**

  Second function is a little more advanced and, I hope, a little more useful.
    
  - *filePath* - string with absolute path to existent csv-file;  
  - *data* - reference to **AbstractData**-based class object;  
  - *separator* (optional) - delimeter symbol;  
  - *codec* (optional) - pointer to the codec object.  

  Function will save content of the file in *data* object, using virtual 
  function **AbstractData::addRow(QStringList)**. If you pass to the 
  function **readToData()** object of class **StringData** or 
  **VariantData**, elements of csv-file will be saved in them as strings.
    
  If you are not happy with this fact, you can create your own
  **AbstractData**-based container class and implement function
  **addRow(QStringList)** in a way you want it.
    
  For example, if you know, that each row of your csv-file contains 3 elements
  (integer value, floating-point value and string), then in function
  **addRow(QStringList)** you can convert first element of **QStringList**
  to int, second - to double and save all three elements to some 
  internal container (or do with them whatever you want).

#### Writer
Use **Writer** class to write to csv-files. It's simpler than **Reader**. It has
only one function! Here it is:

```cpp
bool Writer::write(const QString& filePath,
                   const AbstractData& data,
                   const QString& separator,
                   const WriteMode& mode,
                   const QStringList& header,
                   const QStringList& footer,
                   QTextCodec* codec)
```

- *filePath* - string with absolute path to csv-file (new or existent);
- *data* - object, that contains information that you want to write to csv-file.  
**Writer** internally will use **QStringList AbstractData::rowValues(int)**
function to get row values;
- *separator* (optional) - delimeter symbol (default symbol is comma - ",");
- *mode* (optional) - write mode flag.  
If it set to **WriteMode::REWRITE** and csv-file exist, then csv-file will be
rewritten. If *mode* set to **WriteMode::APPEND** and csv-file exist, then new
information will be appended to the end of the file.  
By default mode set to **WriteMode::REWRITE**.
- *header* (optional) - strings that will be written at the beginning of the file, separated
with defined separator (empty by default);
- *footer* (optional) - strings that will be written at the end of the file, separated
with defined separator (empty by default);
- *codec* (optional) - pointer to the codec object that will be used 
to write data to the file (by default it is codec for locale).

## Requirements
Qt 4.8 and higher.  
It is quite possible, that library will be successfully built with older Qt
versions (4.7, 4.6, ...).

## Build
```bash
cd /path/to/folder/with/qtcsv
qmake -r
make
```

If you want to run tests, then do this:
```bash
cp ./src/libqtcsv.so.1 ./tests
make check
```

## Examples
Lets create example Qt project, that will use *qtcsv* library. We suppose, that
you use Ubuntu 12.04 and already have installed Qt Framework with QtCreator
and have read [Requirements](#requirements) section.

1. Open QtCreator and create new subdirs project (File -> New file or Project
-> Other Project -> Subdirs Project) with name MyProject.
2. Enter settings of our new project and clear flag *Shadow build*.
3. Add new console subproject to MyProject. Call it MyApp.
4. Clone repository of *qtcsv* library into MyProject folder. Via console:

    ```bash
    cd /path/to/MyProject
    git clone https://github.com/iamantony/qtcsv.git
    ```
So the structure of folder MyProject will look like this:
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

7. Edit file ./MyProject/MyApp/main.cpp

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
        varData << first << second;
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

[1]: https://github.com/iamantony
[2]: http://en.wikipedia.org/wiki/Comma-separated_values
[3]: https://github.com/iamantony/qtcsv/blob/master/src/include/reader.h
[4]: https://github.com/iamantony/qtcsv/blob/master/src/include/writer.h
[5]: https://github.com/iamantony/qtcsv/blob/master/src/include/abstractdata.h
[6]: https://github.com/iamantony/qtcsv/blob/master/src/include/stringdata.h
[7]: https://github.com/iamantony/qtcsv/blob/master/src/include/variantdata.h
