# qtcsv

[![Build Status](https://travis-ci.org/iamantony/qtcsv.svg?branch=master)](https://travis-ci.org/iamantony/qtcsv)

Author: [Antony Cherepanov][mypage]  
E-mail: antony.cherepanov@gmail.com

Small easy-to-use library for reading and writing [csv-files][csvwiki]
in Qt. Tested on Ubuntu 12.04 with gcc 4.6.3, Qt 4.8 and higher.

## Table of contents
* [Quick Example](#quick-example)
* [Usage](#usage)
  * [AbstractData](#abstractdata)
  * [StringData](#stringdata)
  * [VariantData](#variantdata)
  * [Reader](#reader)
  * [Writer](#writer)
* [Requirements](#requirements) 
* [Build](#build)
* [Examples](#examples)
* [Other](#other)

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
There are three main classes: **[_Reader_][reader]**,
**[_Writer_][writer]** and **[_AbstractData_][absdata]**.

#### AbstractData
**[_AbstractData_][absdata]** is a pure abstract class that provide
interface for a container class. Here is how it looks:

```cpp
class AbstractData
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

As you can see, **_AbstractData_** declare virtual functions for adding new rows,
getting rows values, clearing all information and so on. Basic stuff for a
container class.

If you have said *Pure Abstract Class*, you must also say *Implementation*.
Don't worry, we have some:

#### StringData
**[_StringData_][strdata]** have the same interface as **_AbstractData_** (plus
some useful functions for inserting rows, removing rows and so on) and stores
all data as strings. It's useful when information that you want to save
in csv-file is represented as strings.

#### VariantData
If you store information in different types - integers, floating point
values, strings or (almost) anything else (example: [1, 3.14, "check"]) -
and you don't want to manually transform each element to string, then you
can use **_QVariant_** magic. Wrap your data into **_QVariants_** and pass it to
**[_VariantData_][vardata]** class.

#### Reader
Use **[_Reader_][reader]** class to read csv-files. It's very simple.
It has only two functions:

1. Read data to **_QList\<QStringList\>_**

```cpp
QList<QStringList> readToList(const QString& filePath,
                              const QString& separator,
                              const QString& textDelimeter,
                              QTextCodec* codec);
```

  - *filePath* - string with absolute path to existent csv-file 
  (example: "/home/user/my-file.csv");  
  - *separator* (optional) - delimeter symbol, that separate elements 
  in a row (by default it is comma - ",");  
  - *textDelimeter* (optional) - text delimeter symbol that enclose
  each element in a row (by default it is double quoute - ");
  - *codec* (optional) - pointer to the codec object that will be used 
  to read data from the file (by default it is UTF-8 codec).  
    
  As a result function will return **_QList\<QStringList\>_**
  that holds content of the file. If all went smooth, list will not be 
  empty and size of it will be equal to the number of rows in csv-file.
  Each **_QStringList_** will contain elements of the corresponding row.

2. Read data to **_AbstractData_**-based container

```cpp
bool readToData(const QString& filePath,
                AbstractData& data,
                const QString& separator,
                const QString& textDelimeter,
                QTextCodec* codec);
```

  Second function is a little more advanced and, I hope, a little more useful.
    
  - *filePath* - string with absolute path to existent csv-file;  
  - *data* - reference to **_AbstractData_**-based class object;  
  - *separator* (optional) - delimeter symbol;  
  - *textDelimeter* (optional) - text delimeter symbol;  
  - *codec* (optional) - pointer to the codec object.  

  Function will save content of the file in *data* object, using virtual 
  function **_AbstractData::addRow(QStringList)_**. If you pass to the 
  function **_Reader::readToData()_** object of class **_StringData_** or 
  **_VariantData_**, elements of csv-file will be saved in them as strings.
    
  If you are not happy with this fact, you can create your own
  **_AbstractData_**-based container class and implement function
  **_addRow(QStringList)_** in a way you want it.
    
  For example, if you know, that each row of your csv-file contains 3 elements
  (integer value, floating-point value and string), then in function
  **_addRow(QStringList)_** you can convert first element of **_QStringList_**
  to int, second - to double and save all three elements to some 
  internal container (or do with them whatever you want).

#### Writer
Use **[_Writer_][writer]** class to write to csv-files. It has only one function:

```cpp
bool Writer::write(const QString& filePath,
                   const AbstractData& data,
                   const QString& separator,
                   const QString& textDelimeter,
                   const WriteMode& mode,
                   const QStringList& header,
                   const QStringList& footer,
                   QTextCodec* codec)
```

- *filePath* - string with absolute path to csv-file (new or existent);
- *data* - object, that contains information that you want to write to csv-file.  
**_Writer_** internally will use **_QStringList AbstractData::rowValues(int)_**
function to get row values;
- *separator* (optional) - delimeter symbol (by default it is comma - ",");
- *textDelimeter* (optional) - text delimeter symbol that enclose
each element in a row (by default it is double quoute - ");
- *mode* (optional) - write mode flag.  
If it set to **_WriteMode::REWRITE_** and csv-file exist, then csv-file will be
rewritten. If *mode* set to **_WriteMode::APPEND_** and csv-file exist, then new
information will be appended to the end of the file.  
By default mode set to **_WriteMode::REWRITE_**.
- *header* (optional) - strings that will be written at the beginning of the file, separated
with defined separator (empty by default);
- *footer* (optional) - strings that will be written at the end of the file, separated
with defined separator (empty by default);
- *codec* (optional) - pointer to the codec object that will be used 
to write data to the file (by default it is UTF-8 codec).

**_Writer_** uses *CRLF* as line ending symbols in accordance with [standard][rfc].
If element of the row contains separator symbol or line ending symbols, such
element will be enclosed by text delimeter symbols (or double quoute if you have set
empty string as text delimeter symbol).

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
If you want to try *qtcsv*, you can download [qtcsv-example project][qtcsv-example].
Don't forget to read README file!

## Other
If you want to know more about csv-file format, read [RFC 4180][rfc] standard.

Also on [this page][csvlint] you can find useful tips about how should look
proper csv-file.

[mypage]: https://github.com/iamantony
[csvwiki]: http://en.wikipedia.org/wiki/Comma-separated_values
[reader]: https://github.com/iamantony/qtcsv/blob/master/src/include/reader.h
[writer]: https://github.com/iamantony/qtcsv/blob/master/src/include/writer.h
[absdata]: https://github.com/iamantony/qtcsv/blob/master/src/include/abstractdata.h
[strdata]: https://github.com/iamantony/qtcsv/blob/master/src/include/stringdata.h
[vardata]: https://github.com/iamantony/qtcsv/blob/master/src/include/variantdata.h
[qtcsv-example]: https://github.com/iamantony/qtcsv-example
[rfc]: http://tools.ietf.org/pdf/rfc4180.pdf
[csvlint]: http://csvlint.io/about
