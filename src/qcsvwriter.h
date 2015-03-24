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
	static bool Write(const QString &t_filePath,
					  const QCSVData &t_data,
					  const QString &t_separator = ",");
};

#endif // QCSVWRITER_H
