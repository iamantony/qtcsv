#include "contentiterator.h"

#include <QString>
#include <QStringList>

#include "include/abstractdata.h"
#include "sources/symbols.h"

using namespace QtCSV;

ContentIterator::ContentIterator(const AbstractData& data,
                                 const QString& separator,
                                 const QString& textDelimeter,
                                 const QStringList& header,
                                 const QStringList& footer,
                                 int chunkSize) :
    m_data(data), m_separator(separator), m_textDelimeter(textDelimeter),
    m_header(header), m_footer(footer), m_chunkSize(chunkSize), m_dataRow(-1),
    atEnd(false)
{
}

// Check if content contains information
// @output:
// - bool - True if content is empty, False otherwise
bool ContentIterator::isEmpty() const
{
    return m_data.isEmpty() && m_header.isEmpty() && m_footer.isEmpty();
}

// Check if content still has chunks of information to return
// @output:
// - bool - True if class can return next chunk of information, False otherwise
bool ContentIterator::hasNext() const
{
    return !atEnd;
}

// Get next chunk of information
// @input:
// - QString - next chunk of information. If there is no more information to
// return, will return empty string
QString ContentIterator::getNext()
{
    // Check if we have already get to the end of the content
    if ( atEnd )
    {
        return QString();
    }

    QString content;
    int rowsNumber = 0;

    // Initially m_dataRow have negative value. It indicates, that clien called
    // this function first time. In this case at the beginning of the chunk
    // we should place header information. And than set m_dataRow to the index
    // of the first row in main data container.
    if ( m_dataRow < 0 )
    {
        if ( false == m_header.isEmpty() )
        {
            content.append(composeRow(m_header));
            ++rowsNumber;
        }

        m_dataRow = 0;
    }

    // Check if m_dataRow is less than number of rows in m_data. If this is
    // true, add to the chunk information from the m_data. Otherwise, this means
    // that we already have passed all the rows in the m_data.
    if ( m_dataRow < m_data.rowCount() )
    {
        int endRow = qMin(m_dataRow + m_chunkSize - rowsNumber,
                          m_data.rowCount());
        for ( int i = m_dataRow; i < endRow; ++i, ++m_dataRow, ++rowsNumber )
        {
            content.append(composeRow(m_data.rowValues(i)));
        }
    }

    // If we still have place in chunk, try to add footer information to it.
    if ( rowsNumber < m_chunkSize )
    {
        if ( false == m_footer.isEmpty() )
        {
            content.append(composeRow(m_footer));
            ++rowsNumber;
        }

        // At this point chunk contains the last information - footer. That
        // means that we get to the end of content.
        atEnd = true;
    }

    return content;
}

// Compose row string from values
// @input:
// - values - list of values in rows
// @output:
// - QString - result row string
QString ContentIterator::composeRow(const QStringList& values) const
{
    QStringList rowValues = values;
    const QString twoDelimeters = m_textDelimeter + m_textDelimeter;
    for (int i = 0; i < rowValues.size(); ++i)
    {
        rowValues[i].replace(m_textDelimeter, twoDelimeters);

        QString delimeter = m_textDelimeter;
        if (delimeter.isEmpty() &&
                (rowValues.at(i).contains(m_separator) ||
                 rowValues.at(i).contains(CR) ||
                 rowValues.at(i).contains(LF)))
        {
            delimeter = DOUBLE_QUOTE;
        }

        rowValues[i].prepend(delimeter);
        rowValues[i].append(delimeter);
    }

    QString result = rowValues.join(m_separator);
    result.append(LF);

    return result;
}
