#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "abstractdata.h"
#include "variantdata.h"
#include "writer.h"

using namespace QtCSV;

// Write data to .csv file
// @input:
// - filePath - string with path to csv file. If it is relative path,
// file will be created in project path. If file already exist, it will
// be overwritten.
// - data - not empty data that should be written to .csv file
// - separator - type of elements separator
// @output:
// - bool - True if data was written to the file, otherwise False
bool Writer::write(const QString &filePath, const AbstractData &data,
				   const Separator &separator)
{
	return write(filePath, data, GetSeparator(separator));
}

bool Writer::write(const QString &filePath, const AbstractData &data,
				   const QString &separator)
{
	if ( true == filePath.isEmpty() ||
		 true == data.isEmpty() ||
		 true == separator.isEmpty() )
	{
		qDebug() << __func__ << "Error - invalid arguments";
		return false;
	}

	if ( false == checkFile(filePath) )
	{
		qDebug() << __func__ << "Error - wrong file path/name:" << filePath;
		return false;
	}

	QFile csvFile;
	csvFile.setFileName(filePath);

	bool fileOpened = csvFile.open(QIODevice::WriteOnly | QIODevice::Text);
	if ( false == fileOpened )
	{
		qDebug() << __func__ << "Error - can't open file:" << filePath;
		return false;
	}

	QTextStream stream;
	stream.setDevice(&csvFile);

	int rowsNum = data.getNumberOfRows();
	for (int i = 0; i < rowsNum; ++i)
	{
		QStringList rowValues= data.getRowValues(i);
		for ( QString &val : rowValues )
		{
			stream << val << separator;
		}

		stream << endl;
	}

	csvFile.close();

	return true;
}

bool Writer::write(const QString &filePath, const VariantData &data,
				   const Separator &separator)
{
	return write(filePath, data, GetSeparator(separator));
}

bool Writer::write(const QString &filePath, const VariantData &data,
				   const QString &separator)
{
	if ( true == filePath.isEmpty() ||
		 true == data.isEmpty() ||
		 true == separator.isEmpty() )
	{
		qDebug() << __func__ << "Error - invalid arguments";
		return false;
	}

	if ( false == checkFile(filePath) )
	{
		qDebug() << __func__ << "Error - wrong file path/name:" << filePath;
		return false;
	}

	QFile csvFile;
	csvFile.setFileName(filePath);

	bool fileOpened = csvFile.open(QIODevice::WriteOnly | QIODevice::Text);
	if ( false == fileOpened )
	{
		qDebug() << __func__ << "Error - can't open file:" << filePath;
		return false;
	}

	QTextStream stream;
	stream.setDevice(&csvFile);

	QStringList headlines = data.getHeadlines();
	if ( false == headlines.isEmpty() )
	{
		for ( int i = 0; i < headlines.size(); ++i )
		{
			stream << headlines.at(i) << separator;
		}

		stream << endl;
	}

	int rowsNum = data.getNumberOfRows();
	for (int i = 0; i < rowsNum; ++i)
	{
		QStringList rowValues = data.getRowValues(i);
		for ( QString &val : rowValues )
		{
			stream << val << separator;
		}

		stream << endl;
	}

	csvFile.close();

	return true;
}

// Check if path to file is valid
// @input:
// - filePath - string with absolute path to csv-file
// @output:
// - bool - True if file is OK, else False
bool Writer::checkFile(const QString &filePath)
{
	QFileInfo fileInfo(filePath);
	if ( fileInfo.isAbsolute() && "csv" == fileInfo.completeSuffix() )
	{
		return true;
	}

	return false;
}
