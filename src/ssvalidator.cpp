#include "ssvalidator.h"
#include <QtShadowsocks>

QStringList SSValidator::supportedMethodList()
{
    QList<QByteArray> methodBA = QSS::Cipher::getSupportedMethodList();
    QStringList methodList;
    for (const QByteArray &method : methodBA) {
        methodList.push_back(QString(method).toUpper());
    }
    return methodList;
}

bool SSValidator::validate(QString input)
{
    //must begin with ss:// to distinguish from random base64 encoded strings
    if (input.startsWith("ss://")) {
        input.remove(0, 5);
        QString decode(QByteArray::fromBase64(QByteArray(input.toStdString().c_str())));
        QStringList decList = decode.split(':');
        if (decList.size() < 3) {
            return false;
        }

        //Validate Method
        QString method = decList.first().toUpper();
        if (method.endsWith("-AUTH")) {
            method.remove("-AUTH");
        }
        if (!validateMethod(method)) {
            return false;
        }

        //Validate Port
        QString port = decList.last();
        if (!validatePort(port)) {
            return false;
        }

        //Validate whether server and password exist
        QStringList pwdServer = decList.at(1).split('@');
        if (pwdServer.size() < 2) {
            return false;
        }

        //it seems acceptable now
        return true;
    }
    else {
        return false;
    }
}

bool SSValidator::validatePort(const QString &port)
{
    bool ok;
    port.toUShort(&ok);
    return ok;
}

bool SSValidator::validateMethod(const QString &method)
{
    static const QStringList validMethodList = supportedMethodList();
    return validMethodList.contains(method, Qt::CaseInsensitive);
}
