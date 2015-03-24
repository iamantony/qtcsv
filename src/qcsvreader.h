#ifndef QCSVREADER_H
#define QCSVREADER_H

#include <QList>
#include <QStringList>

#include "qcsvdata.h"
#include "qtcsv_global.h"

class QTCSVSHARED_EXPORT QCSVReader
{
	// == METHODS ==
public:
	// Read .csv file to QList<QStringList>
	static QList<QStringList> ReadToList(const QString &filePath,
								   const QString &separator = ",");

	// Read .csv file to QCSVData
	static QCSVData ReadToData(const QString &filePath,
						 const QString &separator = ",");
};

#endif // QCSVREADER_H
