#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QString>
#include <QVariant>

class DBManager
{
    public:
        const QString userTableName = "user";
        const QString userInfoTableName = "user_information";
        const QString userAddiInfoTableName = "additional_info";

        DBManager(const QString& path);

        bool isOpen() const;
        bool createTables();
        bool removeTables();
        bool close();

        int userExist(const int id_user);
        int insertUser(const int id_user);
        bool updateUser(const int id_user, const bool active);
        bool deleteUser(const int id_user);

        int userInformationExist(const int id_user_information);
        int addUserInfo(const QMap<QString, QVariant> data);
        bool deleteUserInfo(const int idExtraInfo);
        //bool updateUserInfo(const QMap<QString, QString> data);//sacar

        int insertAdditionalUserInfo(const QMap<QString, QVariant> data);
        bool deleteAdditionalUserInfo(const int idAddiInfo);

        QVector<QStringList> getUserInfo(const int id);
        QVector<QStringList> getCommentsUserInfo(const int id_user, const int id_info);
        QVector<QStringList> getchartDataList(const QMap<QString, QVariant> filterDataList);
        QString getHoursByStatus(const QString initDate, const QString finalDate);
        QVector<QStringList> getTotalHoursByStatus(const QMap<QString, QVariant> filterDataList);

    private:
        QSqlDatabase cdb;
};

#endif // DBMANAGER_H

