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
    if (s == "ENCODE") {
        translateString(true);
    } else if (s == "DECODE") {
        translateString(false);
    } else if (s == "ENCODE_FILE") {
 
    } else if (s == "DECODE_FILE") {

    } else if (s == "EXIT") {

    }
}

const void Encoder::translateString(bool stringToEncode)
{
    QString textToTranslate = _command.right(_command.size() - _command.indexOf(" ") - 1).toLower();
    
    if (stringToEncode) // ENCODE
    {
        for (int i = 0; i < textToTranslate.length(); ++i)
        {
            if (_dictionary.find(textToTranslate.at(i)) == _dictionary.end())
            {
                throw NonExistingPairException();
            }
            _translatedString += QString(_dictionary[textToTranslate.at(i)]);
        }
    }
    else // DECODE
    {
        QString possibleValue = "";
        for (int i = 0; i < textToTranslate.length(); ++i)
        {
            possibleValue += QString(textToTranslate.at(i));
            QMapIterator<QChar, QString> d_it(_dictionary);
            while (d_it.hasNext())
            {
                d_it.next();
                if (d_it.value() == possibleValue)
                {
                    _translatedString += QString(d_it.key());
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