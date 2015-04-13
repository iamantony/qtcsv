#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "filechecker.h"
#include "reader.h"

using namespace QtCSV;

// Read .csv file to QList<QStringList>
// @input:
// - filePath - string with absolute path to .csv file
// - separator - separator symbol
// @output:
// - QList<QStringList> - list of elementsfrom csv-file as strings
QList<QStringList> Reader::readToList(const QString &filePath,
										  const QString &separator)
{
	if ( true == filePath.isEmpty() || true == separator.isEmpty() )
	{
		qDebug() << __func__ << "Error - invalid arguments";
		return QList<QStringList>();
	}

	if ( false == CheckFile(filePath) )
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

// Read .csv file to AbstractDatas
bool Reader::readToData(const QString &filePath, AbstractData &data,
						const QString &separator)
{
	if ( true == filePath.isEmpty() || true == separator.isEmpty() )
	{
		qDebug() << __func__ << "Error - invalid arguments";
		return false;
	}

	if ( false == CheckFile(filePath) )
	{
		qDebug() << __func__ << "Error - wrong file path/name:" << filePath;
		return false;
	}

	QFile csvFile;
	csvFile.setFileName(filePath);

	bool fileOpened = csvFile.open(QIODevice::ReadOnly | QIODevice::Text);
	if ( false == fileOpened )
	{
		qDebug() << __func__ << "Error - can't open file:" << filePath;
		return false;
	}

	QTextStream stream;
	stream.setDevice(&csvFile);

	while ( false == stream.atEnd() )
	{
		QString line = stream.readLine();
		data.addRowValues( line.split(separator) );
	}

	csvFile.close();

	return true;
}
