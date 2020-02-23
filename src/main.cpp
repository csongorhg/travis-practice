#include <QCoreApplication>
#include <QDebug>

#include "encoder.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    
    Encoder* encoder = Encoder::getInstance();
    QTextStream stream(stdin); 
    QString userInput;
    
    while (!(encoder->isJsonValid() && encoder->isPathValid()))
    {
        userInput = stream.readLine();
        encoder->setPath(userInput);

        // Read dictionary
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

        // Handle user commands
        userInput = stream.readLine();
        encoder->setCommand(userInput);

        try
        {
            encoder->executeCommand();
            qInfo() << encoder->getTranslatedString();
        }
        catch(const std::exception& ex)
        {
            qInfo() << ex.what();
        }
        
    }   

    app.exit();
}