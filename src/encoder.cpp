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
    if (doc.isNull()) {
        throw JsonParseException();
    }

    _jsonValid = true;
}

bool Encoder::isPathValid() 
{
    return _pathValid;
}

bool Encoder::isJsonValid() 
{
    return _jsonValid;
}

