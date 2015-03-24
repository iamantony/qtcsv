#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "qcsvwriter.h"

// Write data to .csv file
// @input:
// - t_filePath - string with path to csv file. If it is relative path,
// file will be created in project path. If file already exist, it will
// be overwritten.
// - t_data - not empty data that should be written to .csv file
// - t_separator - separator symbol
// @output:
// - true - data was written to the file
// - false - failed to write to the file
bool QCSVWriter::Write(const QString &t_filePath,
					   const QCSVData &t_data,
					   const QString &t_separator)
{
	if ( (true == t_filePath.isEmpty()) ||
		 (true == t_data.IsEmpty()) ||
		 (true == t_separator.isEmpty()) )
	{
		qDebug() << "Write(): Error - invalid arguments";
		return false;
	}

	QFileInfo fileInfo(t_filePath);
	if ( (false == fileInfo.isAbsolute()) ||
		 ("csv" != fileInfo.completeSuffix()) )
	{
		qDebug() << "Write(): Error - wrong file path/name";
		return false;
	}

	QFile csvFile;
	csvFile.setFileName(t_filePath);

	bool fileOpened = csvFile.open(QIODevice::WriteOnly);
	if ( false == fileOpened )
	{
		qDebug() << "Write(): Error - can't open file!";
		return false;
	}

	QTextStream streamToFile;
	streamToFile.setDevice(&csvFile);

	QStringList headlines = t_data.GetHeadlines();
	if ( false == headlines.isEmpty() )
	{
		for ( int i = 0; i < headlines.size(); ++i )
		{
			streamToFile << headlines.at(i) << t_separator;
		}

		streamToFile << endl;
	}

	int rowsNum = t_data.GetRowsNum();
	QStringList rowValues;
	for (int i = 0; i < rowsNum; ++i)
	{
		bool rowOk = t_data.GetRowValues(i, &rowValues);
		if ( false == rowOk )
		{
			qDebug() << "Write(): Warning: invalid row number: " << i;
			rowValues.clear();
		}

		for ( int j = 0; j < rowValues.size(); ++j )
		{
			streamToFile << rowValues.at(j) << t_separator;
		}

		streamToFile << endl;
		rowValues.clear();
	}

	csvFile.close();

	return true;
}
