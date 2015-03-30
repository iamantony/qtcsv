#ifndef QCSVWRITER_H
#define QCSVWRITER_H

#include <QString>

#include "separator.h"
#include "qtcsv_global.h"

namespace QtCSV
{
	class AbstractData;
	class VariantData;

	class QTCSVSHARED_EXPORT Writer
	{
	public:
		// Write data to .csv file
		static bool write(const QString &filePath,
						  const AbstractData &data,
						  const Separator &separator = Separator::COMMA);

		static bool write(const QString &filePath,
						  const AbstractData &data,
						  const QString &separator = ",");

		static bool write(const QString &filePath,
						  const VariantData &data,
						  const Separator &separator = Separator::COMMA);

		static bool write(const QString &filePath,
						  const VariantData &data,
						  const QString &separator = ",");
	};
}

#endif // QCSVWRITER_H
