#include "dbmanager.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlQuery>
#include <QString>
#include <QDateTime>

DBManager::DBManager(const QString &path)
{
    cdb = QSqlDatabase::addDatabase("QSQLITE");
    cdb.setDatabaseName(path);

    if (!cdb.open())
    {
        qDebug() << "Error: connection with database fail";
    }else{
        qDebug() << "Database: connection ok";
    }
}

bool DBManager::isOpen() const
{
    return cdb.isOpen();
}

bool DBManager::createTables()
{
    bool success = false;
    QString sql = "";

    QVector<QString> tableName;
    tableName.insert(0, "user_information");
    tableName.insert(1, "additional_info");
    tableName.insert(2, "user");

    //DB tables
    QVector<QString> tables;
    tables.insert(0,"CREATE TABLE user_information(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,id_user INTEGER NOT NULL,date TEXT NOT NULL,latitude REAL,longitude REAL,status INTEGER NOT NULL,type BOOLEAN NOT NULL)");
    tables.insert(1,"CREATE TABLE additional_info (id integer PRIMARY KEY AUTOINCREMENT, id_user_info INTEGER NOT NULL, comment TEXT, active BOOLEAN NOT NULL)");
    tables.insert(2,"CREATE TABLE user (id integer PRIMARY KEY AUTOINCREMENT,user int NOT NULL,active boolean NOT NULL)");

    for(int i = 0; i < tableName.length(); i++)
    {
        QSqlQuery query;
        query.prepare("SELECT count(*) FROM sqlite_master WHERE type='table' AND name= (:name)");
        query.bindValue(":name", tableName[i]);
        query.exec();

        while(query.next())
        {
           qDebug() << tables[i];
           if(query.value(0).toInt() == 0)
           {
               if (!query.exec(tables[i]))
               {
                   qDebug() << "Couldn't create the table: one might already exist.";
                   success = false;
               }
           }
        }
    }

    return success;
}

bool DBManager::removeTables()
{
    QVector<QString> tableName;
    tableName.insert(0, "user_information");
    tableName.insert(1, "user_register");
    tableName.insert(2, "user");

    for(int i = 0; i < tableName.length(); i++)
    {
        QSqlQuery query;
        query.exec("DROP TABLE " + tableName[i]);
        qDebug() << "borra: " << tableName[i];
    }
    return true;
}

bool DBManager::close()
{
    cdb.close();
    return true;
}

int DBManager::userExist(const int id_user)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM "+DBManager::userTableName+" WHERE user=(:id_user)");
    query.bindValue(":id_user", id_user);
    query.exec();

    while(query.next())
    {
        return query.value(0).toInt();
    }

    return 0;
}

int DBManager::insertUser(const int id_user)
{
    int id = 0;
    int userResponse = DBManager::userExist(id_user);

    if(userResponse == 0){
        QSqlQuery query;
        query.prepare("INSERT INTO "+ DBManager::userTableName +" (user, active) VALUES (:id_user, :active);");
        query.bindValue(":id_user", id_user);
        query.bindValue(":active", true);

        if(query.exec()){
            return query.lastInsertId().toInt();
        }
    }

    return id;
}

bool DBManager::deleteUser(const int id_user)
{
    bool success = true;

    QSqlQuery query;
    query.exec("DELETE FROM "+ DBManager::userTableName +" WHERE user =" + QString::number(id_user));

    if (query.numRowsAffected() < 1) {
        return 0;
    }

    return success;
}

bool DBManager::updateUser(const int id_user, const bool active)
{
    bool success = 1;

    qDebug() << "tabla: " << DBManager::userTableName;

    QSqlQuery query;
    query.prepare("UPDATE "+ DBManager::userTableName +" SET active = (:active) WHERE user = (:id)");
    query.bindValue(":id", id_user);
    query.bindValue(":active", active);
    query.exec();

    if (query.numRowsAffected() < 1) {
        return 0;
    }
    return success;
}

int DBManager::userInformationExist(const int id_user_information)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM "+ DBManager::userInfoTableName +" WHERE id=(:id_user_info)");
    query.bindValue(":id_user_info", id_user_information);
    query.exec();

    while(query.next()){
        return query.value(0).toInt();
    }
    return 0;
}

//--------------------------------------------

int DBManager::addUserInfo(const QMap<QString, QVariant> data)
{
    int success = 0;
    int userResponse = DBManager::userExist(data.value("id_user").toInt());

    if(userResponse != 0)
    {
        QSqlQuery query;
        query.prepare("INSERT INTO "+ DBManager::userInfoTableName +"(id_user, date, latitude, longitude, status, type) VALUES (:id_user, :date, :latitude, :longitude, :status, :type)");
        query.bindValue(":id_user", userResponse);
        query.bindValue(":date", data.value("date").toString());
        query.bindValue(":latitude", data.value("latitude").toDouble());// -34.6546599
        query.bindValue(":longitude", data.value("longitude").toDouble());//-58.7262101)
        query.bindValue(":status", data.value("status").toInt()); //1,2,3,4
        query.bindValue(":type", data.value("type").toBool()); //true or false
        bool response = query.exec();

        qDebug() << query.lastInsertId().toLongLong();
        success = query.lastInsertId().toLongLong();

        if(!response){
           return 0;
        }

    }else{
        return 0;
    }

    return success;
}

bool DBManager::deleteUserInfo(const int id)
{
    bool success = 1;

    QSqlQuery query;
    query.prepare("DELETE FROM "+ DBManager::userInfoTableName +" WHERE id = (:id)");
    query.bindValue(":id", id);
    query.exec();

    if (query.numRowsAffected() < 1) {
        return 0;
    }

    return success;
}

/*dont use
bool DBManager::updateUserInfo(const QMap<QString, QString> UserData)
{

}*/

//------------------------------------------------

int DBManager::insertAdditionalUserInfo(const QMap<QString, QVariant> data)
{
    int userInfoResponse = DBManager::userInformationExist(data.value("id_user_info").toInt());

    qDebug() << userInfoResponse;

    if(userInfoResponse != 0){
        QSqlQuery query;
        query.prepare("INSERT INTO "+ DBManager::userAddiInfoTableName +"(id_user_info, comment, active) VALUES (:id_user_info, :comment, :active)");
        query.bindValue(":id_user_info", userInfoResponse);
        query.bindValue(":comment", data.value("comment").toString());
        query.bindValue(":active", data.value("active").toBool()); //true or false
        bool response = query.exec();

        if(!response)
        {
           return 0;
        }else{
            return query.lastInsertId().toLongLong();
        }

    }else{
        return 0;
    }
}



bool DBManager::deleteAdditionalUserInfo(const int idAddiInfo)
{
    bool success = 1;

    QSqlQuery query;
    query.prepare("DELETE FROM "+ DBManager::userAddiInfoTableName +" WHERE id = (:id)");
    query.bindValue(":id",idAddiInfo);
    query.exec();

    if (query.numRowsAffected() < 1) {
        return 0;
    }
    return success;
}


QVector<QStringList> DBManager::getUserInfo(const int id)
{
    QVector<QStringList> list;

    QSqlQuery query;
    query.prepare("SELECT * FROM "+DBManager::userInfoTableName+" WHERE id = (:id)");
    query.bindValue(":id",id);
    query.exec();

    while (query.next())
    {
        QSqlRecord record = query.record();
        QStringList tmp;

        for(int i=0; i < record.count(); i++)
        {
            tmp << record.value(i).toString();
        }

        list.append(tmp);
    }

    return list;
}

QVector<QStringList> DBManager::getCommentsUserInfo(const int id_user, const int id_info)
{
    int id = DBManager::userExist(id_user);
    QVector<QStringList> list;

    if(id != 0){
        QSqlQuery query;
        query.prepare("SELECT ai.id, ai.id_user_info, ai.comment,ai.active FROM "+DBManager::userInfoTableName+" AS ui INNER JOIN "+DBManager::userAddiInfoTableName+" AS ai ON ui.id = ai.id_user_info WHERE ui.id_user = (:id_user) AND ui.id = (:id_info)");
        query.bindValue(":id_user",id_user);
        query.bindValue(":id_info",id_info);
        query.exec();

        while (query.next())
        {
            QSqlRecord record = query.record();
            QStringList tmp;

            for(int i=0; i < record.count(); i++)
            {
                tmp << record.value(i).toString();
            }

            list.append(tmp);
        }

        return list;
    }
}

QVector<QStringList> DBManager::getchartDataList(const QMap<QString, QVariant> filterDataList)
{
    int id = DBManager::userExist(filterDataList.value("id_user").toInt());
    QVector<QStringList> list;

    if(id != 0){
        QSqlQuery query;

        query.prepare("SELECT ui.id, ui.id_user, ui.date AS initdate, (((SELECT JulianDay(gui.date) AS finaldate FROM user_information AS gui  WHERE gui.id > ui.id AND gui.id_user = (:id_user) ORDER BY gui.id ASC LIMIT 1) - JulianDay(ui.date))* 24) AS hours, ui.status, ui.type FROM user_information AS ui WHERE ui.date BETWEEN (:initDate) AND (:finalDate) AND id_user=(:id_user) ORDER BY ui.id ASC");
        query.bindValue(":id_user",id);
        query.bindValue(":initDate",filterDataList.value("initDate").toString());
        query.bindValue(":finalDate",filterDataList.value("finalDate").toString());
        query.exec();

        QVector<QStringList> list;

        while (query.next())
        {
            QSqlRecord record = query.record();
            QStringList tmp;

            for(int i=0; i < record.count(); i++)
            {
                tmp << record.value(i).toString();
            }

            list.append(tmp);
        }
        return list;

    }

    //return 0;
}

/*
QString DBManager::getHoursByStatus(QString initDate, QString finalDate)
{
    QDateTime dateTimeInit(QDateTime::fromString(initDate, "yyyy-MM-ddTHH:mm:ss.zzzZ"));
    QDateTime dateTimeFinal(QDateTime::fromString(finalDate, "yyyy-MM-ddTHH:mm:ss.zzzZ"));

    double secondsDiff = dateTimeInit.secsTo(dateTimeFinal);
    double diffHours = (secondsDiff / 3600);

    return QString::number(diffHours);
}
*/

QVector<QStringList> DBManager::getTotalHoursByStatus(const QMap<QString, QVariant> filterDataList)
{
    int id = DBManager::userExist(filterDataList.value("id_user").toInt());
    QVector<QStringList> list;

    if(id != 0){
        QSqlQuery query;
        query.prepare("SELECT ui.status, SUM(((SELECT JulianDay(gui.date) AS finaldate FROM user_information AS gui WHERE gui.id > ui.id AND gui.id_user = (:id_user) ORDER BY gui.id ASC LIMIT 1) - JulianDay(ui.date)) * 24) AS total FROM user_information AS ui WHERE ui.date BETWEEN (:initDate) AND (:finalDate) AND ui.id_user=(:id_user) GROUP BY ui.status ORDER BY ui.id ASC");
        query.bindValue(":id_user",id);
        query.bindValue(":initDate",filterDataList.value("initDate").toString());
        query.bindValue(":finalDate",filterDataList.value("finalDate").toString());
        query.exec();

        QVector<QStringList> list;

        while (query.next())
        {
            QSqlRecord record = query.record();

            QStringList tmp;

            for(int i=0; i < record.count(); i++)
            {
                tmp << record.value(i).toString();
            }

            list.append(tmp);
        }
        return list;

    }

}

/*dont use
bool DBManager::updateExtraUserInfo(const QMap<QString, QString> data)
{

}
*/

QSqlDatabase cdb;

