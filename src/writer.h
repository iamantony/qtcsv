#ifndef QCSVWRITER_H
#define QCSVWRITER_H

#include <QString>

#include "separator.h"
#include "data.h"
#include "qtcsv_global.h"

namespace QtCSV
{
	class QTCSVSHARED_EXPORT Writer
	{
	public:
		// Write data to .csv file
		static bool write(const QString &filePath,
						  const Data &data,
						  const Separator &separator = Separator::COMMA);

		// Write data to .csv file
		static bool write(const QString &filePath,
						  const Data &data,
						  const QString &separator = ",");
	};
}

#endif // QCSVWRITER_H
