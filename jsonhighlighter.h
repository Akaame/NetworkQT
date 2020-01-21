#ifndef JSONHIGHLIGHTER_H
#define JSONHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>

struct HighlightElement
{
    QTextCharFormat format;
    QRegularExpression regexp;
};

class JsonHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    JsonHighlighter(QTextDocument* parent);
    ~JsonHighlighter();
protected:
    void highlightBlock(const QString &text) override;
private:
    QList<HighlightElement> rules;
};

#endif // JSONHIGHLIGHTER_H
