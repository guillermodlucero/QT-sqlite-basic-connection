#include "dbmanager.h"
#include "userinfo_global.h"
#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <QDir>
#include <QDateTime>
//#include <QVariant>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    DBManager db(global::db_path);
    qDebug() << global::db_path;

    /*
     * metodos que crean y eliminas las tablas de la base
     */
    //db.createTables();
    //db.removeTables();

    /*
     * Verifica que el usuario enviado exista en la tabla users
     *
     */
    //int idresponse = db.userExist(9);
    //qDebug() << "user exist: " << idresponse;

    /*
     * Inserta el usuario en la tabla users
     */
    //int idresponse = db.insertUser(10);
    //qDebug() << "id que devuelve el usuario insertado: " << idresponse;

    /*
     * Permite cambiar el estado del usuario 1 o 0
     */
    //id de usuario and active boolean
    //bool response = db.updateUser(10, 0);
    //qDebug() << "update tabla user: " << response;

    /*
     *Permite borra un usuario de la base users
     */
    //bool response = db.deleteUser(2);
    //qDebug() << "devuelve el usuario borrado: " << response;

    /*
     *Comprueba si un registro existe en la tabla user_information
     */
    //int idResponse = db.userInformationExist(2);//id de registro
    //qDebug() << "id si existe el registro: " << idResponse;

    /*
     * Guarda la informacion del usuario en la tabla user_information
     */
    /*
    QMap<QString, QVariant> UserData;
    UserData["id_user"] = 9; //id de registro de la tabla user_info
    UserData["date"] = "2017-11-02T00:00:00.00Z";
    UserData["latitude"] = 0.0;
    UserData["longitude"] = 0.0;
    UserData["status"] = 4;//1,2,3,4
    UserData["type"] = 1;//true or false
    qDebug() << "data insert: " << UserData;

    int idResponse = db.addUserInfo(UserData);
    qDebug() << "data insertada: " << idResponse;
    */
    /*
     * Borrar un registro de la tabla por el id
     */
    /*
    bool response = db.deleteUserInfo(73);
    qDebug() << "delete: " << response;
    */
    /*
     *Actualiza un registro de la tabla user_information por el id
     */
    /* dont use
    bool response = db.updateUserInfo(UserData);
    qDebug() << "update tabla user information:" << response;
    */

    /*
     * guarda un comentario en la tabla additional_info,
     */
    /*
    QMap<QString, QVariant> additionalUserInfo;
    additionalUserInfo["id_user_info"] = 66; //id de registro de la tabla user_info
    additionalUserInfo["comment"] = "esto es un comentario 1";
    additionalUserInfo["active"] = 1;//true or false

    int response = db.insertAdditionalUserInfo(additionalUserInfo);
    qDebug() << "inserta informacion de usuario:" << response;
    */
    /*
     * Borra un registro de la tabla additional_info, por el id de registro
     */

    //bool response = db.deleteAdditionalUserInfo(1);
    //qDebug() << "elimina el comentario:" << response;

    /*
     * Obtiene la lista de los comentario guardados de un registro de user_information
     */
    /*
    QVector<QStringList> responseList = db.getCommentsUserInfo(3, 71);
    qDebug() << "devuelve: ";
    qDebug() << responseList;
    */
    /*
     *
     * Obtiene un registro de la tabla user_information por su id
     */
    /*
    QVector<QStringList> responseList = db.getUserInfo(70);
    qDebug() << "devuelve: ";
    qDebug() << responseList;
    */
    /*
     *Obtengo la informacion parael grafico, filtra por fecha inicial, final y id de usuario
     */
    /*
    QMap<QString, QVariant> filterData;
    filterData["id_user"] = 9; //id de usuario
    filterData["initDate"] = "2017-01-00 00:00:00";
    filterData["finalDate"] = "2017-12-00 00:00:00";

    QVector<QStringList> responseList = db.getchartDataList(filterData);
    qDebug() << "devuelve lista de informacion del usuario";
    qDebug() << responseList;
    */
    /*
     *OBtiene el total de horas por cada estado
     */
    /*
    QMap<QString, QVariant> filterData;
    filterData["id_user"] = 9; //id de usuario
    filterData["initDate"] = "2017-01-00 00:00:00";
    filterData["finalDate"] = "2017-12-00 00:00:00";

    QVector<QStringList> responseTotalHoursList = db.getTotalHoursByStatus(filterData);
    qDebug() << "devuelve total de horas";
    qDebug() << responseTotalHoursList;
    */

    db.close();

    return a.exec();
}



