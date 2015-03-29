#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QDebug>

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
// - true - data was written to the file
// - false - failed to write to the files
bool Writer::write(const QString &filePath, const Data &data,
				   const Separator &separator)
{
	return write(filePath, data, GetSeparator(separator));
}

// Write data to .csv file
// @input:
// - filePath - string with path to csv file. If it is relative path,
// file will be created in project path. If file already exist, it will
// be overwritten.
// - data - not empty data that should be written to .csv file
// - separator - separator symbol
// @output:
// - true - data was written to the file
// - false - failed to write to the files
bool Writer::write(const QString &filePath, const Data &data,
				   const QString &separator)
{
	if ( true == filePath.isEmpty() ||
		 true == data.isEmpty() ||
		 true == separator.isEmpty() )
	{
		qDebug() << __func__ << "Error - invalid arguments";
		return false;
	}

	QFileInfo fileInfo(filePath);
	if ( false == fileInfo.isAbsolute() || "csv" != fileInfo.completeSuffix() )
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

	int rowsNum = data.getRowNum();
	QStringList rowValues;
	for (int i = 0; i < rowsNum; ++i)
	{
		bool rowOk = data.getRowValues(i, &rowValues);
		if ( false == rowOk )
		{
			qDebug() << __func__ << "Warning: invalid row number:" << i;
			rowValues.clear();
		}

		for ( int j = 0; j < rowValues.size(); ++j )
		{
			stream << rowValues.at(j) << separator;
		}

		stream << endl;
		rowValues.clear();
	}

	csvFile.close();

	return true;
}
