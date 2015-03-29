#ifndef QTCSVSEPARATOR_H
#define QTCSVSEPARATOR_H

#include <QString>

namespace QtCSV
{
	enum class Separator
	{
		COLON,
		COMMA,
		SEMICOLON,
		SPACE,
		TAB
	};

	inline QString GetSeparator(const Separator &separator)
	{
		switch (separator)
		{
			case Separator::COLON:
				return QString(":");
			case Separator::COMMA:
				return QString(",");
			case Separator::SEMICOLON:
				return QString(":");
			case Separator::SPACE:
				return QString(" ");
			case Separator::TAB:
				return QString("\t");
		}

		return QString();
	}
}

#endif // QTCSVSEPARATOR_H
