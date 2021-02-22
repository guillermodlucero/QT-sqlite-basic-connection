#include "chartdata.h"
#include "dbmanager.h"
#include <QDebug>
#include <QString>

ChartData::ChartData(){

}

void ChartData::getchartDataList()
{
    qDebug() << "getchartDataList()";
    /*
    DBManager db(db_path);

    QMap<QString, QString> filterData;
    filterData["id_user"] = "9"; //id de usuario
    filterData["initDate"] = "2017-01-00 00:00:00:000";
    filterData["finalDate"] = "2017-05-00 00:00:00:000";

    QVector<QStringList> responseList = db.getchartDataList(filterData);
    qDebug() << "devuelve";
    qDebug() << responseList;
    */
}
