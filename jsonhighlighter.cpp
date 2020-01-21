#include "jsonhighlighter.h"

JsonHighlighter::JsonHighlighter(QTextDocument* parent):QSyntaxHighlighter(parent)
{
    HighlightElement numberEl;
    numberEl.regexp = QRegularExpression("[0-9]+");
    auto numberFormat = QTextCharFormat();
    numberFormat.setForeground(Qt::darkMagenta);
    numberEl.format = numberFormat;
    rules.append(numberEl);

    HighlightElement stringEl;
    stringEl.regexp = QRegularExpression("\".*?\"");
    auto stringFormat = QTextCharFormat();
    stringFormat.setForeground(Qt::blue);
    stringEl.format = stringFormat;
    rules.append(stringEl);
}

JsonHighlighter::~JsonHighlighter()
{

}

void JsonHighlighter::highlightBlock(const QString& text)
{
    for (const HighlightElement &rule : qAsConst(rules)) {
           QRegularExpressionMatchIterator matchIterator = rule.regexp.globalMatch(text);
           while (matchIterator.hasNext()) {
               QRegularExpressionMatch match = matchIterator.next();
               setFormat(match.capturedStart(), match.capturedLength(), rule.format);
           }
       }
}

// QT Monitor exe cpu usage and mem usage
// monitor mem leaks
// Json
