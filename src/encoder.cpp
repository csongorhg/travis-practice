#include "encoder.h"

Encoder* Encoder::_instance = 0;

Encoder::Encoder()
{}

Encoder* Encoder::getInstance() 
{
    if (_instance == 0)
    {
        _instance = new Encoder();
    }
    return _instance;
}

const void Encoder::setPath(const QString path)
{
    _path = path;
}

const void Encoder::setCommand(const QString command)
{
    _command = command;
}

const void Encoder::validatePath()
{
    qDebug() << QString(QDir::currentPath());
    qDebug() << _path;
    _pathValid = QFile::exists(_path);
    if (!_pathValid) {
        throw InvalidPathException();
    }
}

const void Encoder::parseJson()
{
    QFile inFile(_path);
    inFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray data = inFile.readAll();
    inFile.close();

    QJsonParseError errorPtr;
    QJsonDocument doc = QJsonDocument::fromJson(data, &errorPtr);
    if (errorPtr.error != QJsonParseError::NoError) {
        throw JsonParseException();
    }

    _jsonValid = true;

    QJsonObject root = doc.object();

    for (QJsonObject::const_iterator it = root.begin(); it != root.end(); ++it)
    {
        if (it.key().size() > 1) {
            throw JsonParseException();
        } 
        _dictionary.insert(it.key().at(0).toLower(), it.value().toString().toLower());
    }
}

const void Encoder::executeCommand()
{
    QString s = _command.split(" ")[0];
    QString translated;
    if (s == "ENCODE") {
        setTranslatedString(translateString(true, _command.right(_command.size() - _command.indexOf(" ") - 1)));
    } else if (s == "DECODE") {
        setTranslatedString(translateString(false, _command.right(_command.size() - _command.indexOf(" ") - 1)));
    } else if (s == "ENCODE_FILE") {
        translateFile(true);
    } else if (s == "DECODE_FILE") {
        translateFile(false);
    } else if (s == "EXIT") {
        qInfo() << "KTHXBYE";
    }
}

const QString Encoder::translateString(bool fromEncode, QString stringToTranslate)
{   
    stringToTranslate = stringToTranslate.toLower();
    QString translatedString = "";
    if (fromEncode) // ENCODE
    {
        for (int i = 0; i < stringToTranslate.length(); ++i)
        {
            if (_dictionary.find(stringToTranslate.at(i)) == _dictionary.end())
            {
                throw NonExistingPairException();
            }
            translatedString += QString(_dictionary[stringToTranslate.at(i)]);
        }
    }
    else // DECODE
    {
        QString possibleValue = "";
        for (int i = 0; i < stringToTranslate.length(); ++i)
        {
            possibleValue += QString(stringToTranslate.at(i));
            QMapIterator<QChar, QString> d_it(_dictionary);
            while (d_it.hasNext())
            {
                d_it.next();
                if (d_it.value() == possibleValue)
                {
                    translatedString += QString(d_it.key());
                    possibleValue = "";
                    break;
                }
            }
        }
        if (!possibleValue.isEmpty())
        {
            throw NonExistingPairException();
        }
    }
    return translatedString;
}

const void Encoder::translateFile(bool fromEncode)
{
    QString fromFilePath = _command.split(" ")[1];
    QString toFilePath = _command.split(" ")[2];

    if (!QFile::exists(fromFilePath))
    {
        throw InvalidPathException();
    }

    QFile fromFile(fromFilePath);
    fromFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray data = fromFile.readAll();
    fromFile.close();

    setTranslatedString(translateString(fromEncode, QString(data)));

    QFile toFile(toFilePath);
    toFile.open(QIODevice::WriteOnly);
    QTextStream out(&toFile);
    out << _translatedString;
    toFile.close();

    _translatedString.clear();
}

const void Encoder::setTranslatedString(const QString translatedString)
{
    _translatedString = translatedString;
}

bool Encoder::isPathValid() const
{
    return _pathValid;
}

bool Encoder::isJsonValid() const
{
    return _jsonValid;
}

const QString Encoder::getTranslatedString() const
{
    return _translatedString;
}