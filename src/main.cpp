#include <QCoreApplication>
#include <QDebug>

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    qInfo() << "C++ Style Info Message";

    return 0;
}