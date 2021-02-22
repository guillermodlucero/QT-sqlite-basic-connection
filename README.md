
# Ejemplo de coneccion QT y SQLite

## Campos tablas

### Estados de los campos **estados** y **tipo** en tabla **user_information**

### estados

* 1: Driving
* 2: Off duty
* 3: On duty not driving
* 4: sleeper bed 

### tipo

* 0: automatico
* 1: manual



## Metodos de clase DBManager

### Crea y eliminar tablas

Metodos que crean y eliminas las tablas de la base

```Java

createTables();
removeTables();

```

### User Exit

Verifica que un usuario existe en la tabla users

Parametro: 
* (int) ID de usuario insertadopreviamente.

```Java

userExist(9);

```

### Inserta el usuario en la tabla users

Parametro: 
* (int) ID de usuario.

```Java

insertUser(10);

```

### Acuatiza el estado del usuario

Parametro: 
* (int) id de usuarioPermite cambiar el estado del usuario 1 o 0
* (bool) estado 1 activo, 2 no activado

```Java

updateUser(10, 1);

```

### Borrar usuario

Parametro:
* (int) id de usuario

```Java

deleteUser(5);

```

### Insertar informacion de usuario

Parametro:
* user_id: id de usuario
* date: fecha en formato "2017-03-10 16:25:00:000"
* latitude:
* longitude
* status: 1 - Driving, 2 - Off duty, 3 - On duty not driving, 4 -sleeper bed 
* type: 1 - carga automatica, 2 - carga manual

```Java

QMap<QString, QVariant> UserData;
UserData["id_user"] = 9; //id de registro de la tabla user_info
UserData["date"] = "2017-11-02T00:00:00.00Z";
UserData["latitude"] = 0.0;
UserData["longitude"] = 0.0;
UserData["status"] = 4;//1,2,3,4
UserData["type"] = 1;//true or false	

db.addUserInfo(UserData);

```
Return:
* id de registro de informacion insertada


##Borrar informacion de usuario

Parametro:
* id: id de registro

```Java

db.deleteUserInfo(8);

```

Return:
* true o false


### Verifica que existe un registro

Parametro:
* id: id de registro de la tabla **user_information**

```Java

db.userInformationExist(8);

```

Return:
* id de registro o 0


### Inserta informacion adicional (comentario)

Parametro:
* id_user_info: id de registro de la tabla **additional_info**
* comment: 
* active:1 - activado, 2 -desactivado

```Java

QMap<QString, QVariant> additionalUserInfo;
additionalUserInfo["id_user_info"] = 66; //id de registro de la tabla user_info
additionalUserInfo["comment"] = "esto es un comentario 1";
additionalUserInfo["active"] = 1;//true or false

db.insertAdditionalUserInfo(additionalUserInfo);

```

Return:
* id de registro

### Borra comentario

Parametro:
* id: id de registro de la tabla **additional_info**

```Java
		
db.deleteAdditionalUserInfo(2);

```

### Obtiene la lista de comentario

Parametro:
* id: id de usuario

```Java
		
db.getCommentsUserInfo(2);

```

Return:
```Java
QVector(
("1", "4", "esto es un comentario 5", "1"), 
("3", "4", "esto es un comentario 2", "1")
)
```


### Obtiene la information para el grafico

Parametro:
* id_user: id de usuario
* initDate: fecha en formato "2017-01-00 00:00:00:000"
* finalDate: fecha en formato "2017-01-00 00:00:00:000"

```Java
	
QMap<QString, QVariant> filterData;
filterData["id_user"] = 9; //id de usuario
filterData["initDate"] = "2017-01-00 00:00:00";
filterData["finalDate"] = "2017-12-00 00:00:00";
db.getchartDataList(filterData);

```

Return:

```Java
		
QVector(
("1", "4", "2017-03-10 16:25:00:000", "1", "1", "0"), 
("2", "4", "2017-03-10 16:25:00:000", "2", "1", "0"), 
("4", "4", "2017-03-10 16:25:00:000", "4", "1", "0")
)

```
#### Campos que devuelve:
id, id_user, date, horas (tiempo en horas que permanecio en el estado), status, type, 


### Obtiene la informacion del usuario

Parametro:
* id_user: id de registro de la tabla


```Java
		
db.getUserInfo(4);

```

Return:

```Java
		
QVector(("4", "4", "2017-03-10 16:25:00:000", "31.59785", "-60.38918", "4", "1"))

```

### Obtiene la cantidad de horas totales por cada estado

Parametro:
* id_user: id de usuario
* initDate: fecha en formato "2017-01-00 00:00:00:000"
* finalDate: fecha en formato "2017-01-00 00:00:00:000"

```Java
	
QMap<QString, QVariant> filterData;
filterData["id_user"] = 9; //id de usuario
filterData["initDate"] = "2017-01-00 00:00:00";
filterData["finalDate"] = "2017-12-00 00:00:00";

QVector<QStringList> responseTotalHoursList = db.getTotalHoursByStatus(filterData);

```

Return:

```Java
		
(
("3", "54"), 
("2", "675"), 
("1", "2084"), 
("4", "774"))

```
#### Campos que devuelve:
status, horas totales (sumatoria de horas totales por estado)
 



