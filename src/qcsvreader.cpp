#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "qcsvreader.h"

// Read .csv file to QList<QStringList>
// @input:
// - t_filePath - string with absolute path to .csv file
// - t_separator - separator symbol
QList<QStringList> QCSVReader::ReadToList(const QString &filePath,
										  const QString &separator)
{
	if ( true == filePath.isEmpty() || true == separator.isEmpty() )
	{
		qDebug() << __func__ << "Error - invalid arguments";
		return QList<QStringList>();
	}

	QFileInfo fileInfo(filePath);
	if ( false == fileInfo.isAbsolute() || "csv" != fileInfo.completeSuffix() )
	{
		qDebug() << __func__ << "Error - wrong file path/name:" << filePath;
		return QList<QStringList>();
	}

	QFile csvFile;
	csvFile.setFileName(filePath);

	bool fileOpened = csvFile.open(QIODevice::ReadOnly | QIODevice::Text);
	if ( false == fileOpened )
	{
		qDebug() << __func__ << "Error - can't open file:" << filePath;
		return QList<QStringList>();
	}

	QTextStream stream;
	stream.setDevice(&csvFile);

	QList<QStringList> data;
	while ( false == stream.atEnd() )
	{
		QString line = stream.readLine();
		data << line.split(separator);
	}

	csvFile.close();

	return data;
}

// TODO
QCSVData QCSVReader::ReadToData(const QString &/*filePath*/,
								const QString &/*separator*/)
{
	return QCSVData();
}
