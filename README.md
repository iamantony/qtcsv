# qtcsv

[![Build Status](https://travis-ci.org/iamantony/qtcsv.svg?branch=master)](https://travis-ci.org/iamantony/qtcsv) [![Build status](https://ci.appveyor.com/api/projects/status/7uv7ghs9uexf08bv/branch/master?svg=true)](https://ci.appveyor.com/project/iamantony/qtcsv/branch/master)

Small easy-to-use library for reading and writing [csv-files][csvwiki]
in Qt.

Tested on:
- Ubuntu 14.04 with gcc 4.8.4, Qt 4.8 and higher
- Windows with MinGW, Qt 5.3 and higher

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
  * [Prebuild step on Windows](#prebuild-step-on-windows)
* [Run tests](#run-tests)
  * [Linux](#linux)
  * [Windows](#windows)
* [Installation](#installation)
* [Examples](#examples)
* [Other](#other)
* [Creators](#creators)

## Quick Example
```cpp
#include <QList>
#include <QStringList>
#include <QDir>
#include <QDebug>

#include "qtcsv/stringdata.h"
#include "qtcsv/reader.h"
#include "qtcsv/writer.h"

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
                                const QString& textDelimiter,
                                QTextCodec* codec);
  ```

  - *filePath* - string with absolute path to existent csv-file
    (example: "/home/user/my-file.csv");
  - *separator* (optional) - delimiter symbol, that separate elements
  in a row (by default it is comma - ",");
  - *textDelimiter* (optional) - text delimiter symbol that enclose
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
                  const QString& textDelimiter,
                  QTextCodec* codec);
  ```

  Second function is a little more advanced and, I hope, a little more useful.

  - *filePath* - string with absolute path to existent csv-file;
  - *data* - reference to **_AbstractData_**-based class object;
  - *separator* (optional) - delimiter symbol;
  - *textDelimiter* (optional) - text delimiter symbol;
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
                   const QString& textDelimiter,
                   const WriteMode& mode,
                   const QStringList& header,
                   const QStringList& footer,
                   QTextCodec* codec)
```

- *filePath* - string with absolute path to csv-file (new or existent);
- *data* - object, that contains information that you want to write to csv-file.
**_Writer_** internally will use **_QStringList AbstractData::rowValues(int)_**
function to get row values;
- *separator* (optional) - delimiter symbol (by default it is comma - ",");
- *textDelimiter* (optional) - text delimiter symbol that enclose
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
element will be enclosed by text delimiter symbols (or double quoute if you have set
empty string as text delimiter symbol).

## Requirements
Qt 4.8 and higher.
It is quite possible, that library will be successfully built with older Qt
versions (4.7, 4.6, ...).

## Build

### Prebuild step on Windows
If you going to build *qtcsv* library on Windows, first of all [check that your PATH variable][path_var] contains paths to _Qt_ and _MinGW_ toolsets. For example, you have installed Qt 5.3 into _C:\Qt_. Then Qt binaries and libraries will be in folder _C:\Qt\5.3\mingw482_32\bin_ and MinGW binaries will be in _C:\Qt\Tools\mingw482_32\bin_. Add these paths to the PATH variable so that Windows would know where to look for _qmake_ and _make_ binaries.

```bash
cd /path/to/folder/with/qtcsv

# Build library
qmake
make

# Build tests
cd ./tests
qmake
make
```

## Run tests
If you want to run tests, then use this commands after build of *qtcsv*:

### Linux
```bash
cd /path/to/folder/with/qtcsv
chmod 777 qtcsv_tests
./qtcsv_tests
```

### Windows
```bash
cd /path/to/folder/with/qtcsv
qtcsv_tests.exe
```

## Installation
On Unix-like OS you can install *qtcsv* library using this command:
```bash
sudo make install
sudo ldconfig -n -v /usr/local/lib
```

This command will copy all compiled files (libqtcsv.so\*) from *"./src"*
folder to *"/usr/local/lib"*. Also all headers files will be copied
from *"./src/include"* folder to *"/usr/local/include/qtcsv"*.

All installation settings are defined in [*./src/src.pro*][src-pro] file.
See *libheaders* and *target* variables.

For additional information, see [Qt documentation][install-files] about
files installation.

## Examples
If you want to try *qtcsv*, you can download [qtcsv-example project][qtcsv-example].
Don't forget to read README file!

## Other
If you want to know more about csv-file format, read [RFC 4180][rfc] standard.

Also on [this page][csvlint] you can find useful tips about how should look
proper csv-file.

## Creators
Author: [Antony Cherepanov][mypage] (antony.cherepanov@gmail.com)  
Contributors: [Patrizio "pbek" Bekerle][pbek], [Furkan "Furkanzmc" Üzümcü][Furkanzmc]

[csvwiki]: http://en.wikipedia.org/wiki/Comma-separated_values
[reader]: https://github.com/iamantony/qtcsv/blob/master/src/include/reader.h
[writer]: https://github.com/iamantony/qtcsv/blob/master/src/include/writer.h
[absdata]: https://github.com/iamantony/qtcsv/blob/master/src/include/abstractdata.h
[strdata]: https://github.com/iamantony/qtcsv/blob/master/src/include/stringdata.h
[vardata]: https://github.com/iamantony/qtcsv/blob/master/src/include/variantdata.h
[src-pro]: https://github.com/iamantony/qtcsv/blob/master/src/src.pro
[install-files]: http://doc.qt.io/qt-5/qmake-advanced-usage.html#installing-files
[qtcsv-example]: https://github.com/iamantony/qtcsv-example
[rfc]: http://tools.ietf.org/pdf/rfc4180.pdf
[path_var]: http://superuser.com/questions/284342/what-are-path-and-other-environment-variables-and-how-can-i-set-or-use-them
[csvlint]: http://csvlint.io/about
[mypage]: https://github.com/iamantony
[pbek]: https://github.com/pbek
[Furkanzmc]: https://github.com/Furkanzmc
