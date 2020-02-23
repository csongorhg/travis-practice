#include <QString>
#include <QFileInfo>
#include <QJsonParseError>
#include <QChar>
#include <QMap>
#include <QVariant>
#include <QDebug>
#include <QJsonObject>
#include <QTextCodec>
#include <QFile>

class InvalidPathException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "ERROR: File doesn't exists.";
  }
};

class JsonParseException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "ERROR: JSON processing has failed.";
  }
};

class NonExistingPairException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "ERROR: Key is not present in the dictionary.";
  }
};

class Encoder
{
  private:
    static Encoder* _instance;
    Encoder();

    QString _path;
    QString _command;
    QString _commandResult;
    QString _translatedString;
    bool _pathValid = false;
    bool _jsonValid = false;

    QMap<QChar, QString> _dictionary;

  public:
    static Encoder* getInstance();
    
    const void setPath(const QString path);
    const void setCommand(const QString command);
    const void validatePath();
    const void parseJson();
    const void executeCommand();
    const void translateString(bool fromEncode, QString stringToTranslate);
    const void translateFile(bool fromEncode);

    bool isPathValid() const;
    bool isJsonValid() const;
    const QString getTranslatedString() const;
};