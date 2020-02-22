#include <QString>
#include <QFileInfo>
#include <QJsonParseError>
#include <QChar>
#include <QMap>
#include <QVariant>
#include <QDebug>
#include <QJsonObject>

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

class Encoder
{
  private:
    static Encoder* _instance;
    Encoder();

    QString _path;
    bool _pathValid = false;
    bool _jsonValid = false;

    QMap<QChar, QString> _dictionary;
 
  public:
    static Encoder* getInstance();
    
    const void setPath(const QString path);
    const void validatePath();
    const void parseJson();

    bool isPathValid();
    bool isJsonValid();
};