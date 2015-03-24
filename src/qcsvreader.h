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
	static QList<QStringList> ReadToList(const QString &t_filePath,
								   const QString &t_separator = ",");
	static QCSVData ReadToData(const QString &t_filePath,
						 const QString &t_separator = ",");
};

#endif // QCSVREADER_H
