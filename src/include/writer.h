#ifndef QCSVWRITER_H
#define QCSVWRITER_H

#include <QString>
#include <QTextStream>

#include "qtcsv_global.h"

namespace QtCSV
{
	class AbstractData;
	class VariantData;

	class QTCSVSHARED_EXPORT Writer
	{
	public:
		enum WriteMode
		{
			REWRITE = 0,
			APPEND
		};

		// Write data to .csv file
		static bool write(const QString &filePath,
						  const AbstractData &data,
						  const QString &separator = ",",
						  const WriteMode &mode = REWRITE);

		static bool write(const QString &filePath,
						  const VariantData &data,
						  const QString &separator = ",",
						  const WriteMode &mode = REWRITE);

	private:
		// Get QIODevice mode
		static QIODevice::OpenMode GetMode(const WriteMode &mode);
	};
}

#endif // QCSVWRITER_H
