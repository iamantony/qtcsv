#ifndef QCSVWRITER_H
#define QCSVWRITER_H

#include <QString>

#include "qcsvdata.h"
#include "qtcsv_global.h"

class QTCSVSHARED_EXPORT QCSVWriter
{
	// == METHODS ==
public:
	// Write data to .csv file
	static bool Write(const QString &filePath,
					  const QCSVData &data,
					  const QString &separator = ",");
};

#endif // QCSVWRITER_H
