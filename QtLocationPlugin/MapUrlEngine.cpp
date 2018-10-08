#include "MapEngine.h"

#include <QRegExp>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTimer>
#include <QString>
#include <QByteArray>
#include <QDebug>

UrlFactory::UrlFactory()
    : _timeout(5 * 1000)

{
}

//-----------------------------------------------------------------------------
UrlFactory::~UrlFactory()
{
}


//-----------------------------------------------------------------------------
QString
UrlFactory::getImageFormat(MapType type, const QByteArray& image)
{
    QString format;
    if(image.size() > 2)
    {
        if((char)image[0] == (char)0xff && (char)image[1] == (char)0xd8)
            format = "jpg";
        else if((char)image[0] == (char)0x89 && (char)image[1] == (char)0x50)
            format = "png";
        else {
            switch (type) {
            case GaodeStreet:
                format = "png";
                break;
            case GaodeSatellite:
                format = "jpg";
                break;
            default:
                qWarning("UrlFactory::getImageFormat() Unknown map id %d", type);
                break;
            }
        }
    }
    return format;
}

//-----------------------------------------------------------------------------
QNetworkRequest
UrlFactory::getTileURL(MapType type, int x, int y, int zoom)
{
    //-- Build URL
    QNetworkRequest request;
    QString url = _getURL(type, x, y, zoom);
    if(url.isEmpty())
        return request;
    request.setUrl(QUrl(url));
    request.setRawHeader("Accept", "*/*");
    request.setRawHeader("User-Agent", _userAgent);
    switch (type) {
    case GaodeStreet:
    case GaodeSatellite:
        request.setRawHeader("Referrer", "https://www.gaode.com/maps/");
        break;
    default:
        break;
    }
    return request;
}


//-----------------------------------------------------------------------------
QString
UrlFactory::_getURL(MapType type, int x, int y, int zoom)
{
    switch (type) {
    case GaodeStreet:
    {
        return QString("http://wprd03.is.autonavi.com/appmaptile?style=7&x=%1&y=%2&z=%3").arg(x).arg(y).arg(zoom);
    }
        break;
    case GaodeSatellite:
    {
         return QString("http://wprd03.is.autonavi.com/appmaptile?style=6&x=%1&y=%2&z=%3").arg(x).arg(y).arg(zoom);
    }
        break;

    default:
        qWarning("Unknown map id %d\n", type);
        break;
    }
    return QString::null;
}


