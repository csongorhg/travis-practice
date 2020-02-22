#include <QCoreApplication>
#include <QDebug>

#include "encoder.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    
    Encoder* encoder = Encoder::getInstance();
    QTextStream stream(stdin); 
    QString path;
    
    while (!(encoder->isJsonValid() && encoder->isPathValid()))
    {
        path = stream.readLine();
        encoder->setPath(path);

        try
        {
            // Validate path
            encoder->validatePath();

            // Parse JSON
            encoder->parseJson();
        } 
        catch (const std::exception& ex)
        {
            qInfo() << ex.what();
            continue;
        }
    }   

    app.exit();
}