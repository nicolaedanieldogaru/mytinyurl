# MyTinyURL
Based on Sample code of cpprestsdk (casablanca)


This repo contains a sample of cpprestsdk server side in very simple format.
sample handles 4 method of http request [put, get,post and delete].
almost every function/class name is a self documentation  of it's functionality.

project structure 

[main.cpp]
[include/handler.h]
[src/hander.cpp]
[src/Base62Generarator.cpp]
[src/dataHandler.cpp]
[src/database.cpp]

How to compile :

cmake .

make

run server with command "./Build/bin/restserver"

[
For mac, mac branch is recommanded.
]

[
For Windows (Visual studio solution) (checkout vs15_v140 branch )
]
##############################################

{#dbms folder is a independent project right now to access database before enable to install some prerequsites}
1)
 install postgresql;
 install pqxx  (sudo apt-get install libpqxx-dev)
 and libpq  if it is not installed with postgresql  ((sudo apt-get install libpq-dev)
 
dbms support can be added ( right now  Postgresql only) by doing following steps 
1) uncomment  line 5 of handler.h 

>//#include "../dbms/include/Dbms.h"

2) for testing uncomment line 43 and 44 of handler.cpp
>	//Dbms* d  = new Dbms();
>   //d->connect();
 
How to complie :

cmake . -DDBMS=ON

make

run server with command "./Build/bin/restserver"
 
now all done . just implement/replace own logic.

How to use it?

1. From command line:
   use command: curl -X POST http://127.0.0.1:34568 -d 'www.your_url.xxx' to create new tiny url in database mapped to your original url
   use command: curl -X GET http://127.0.0.1:34568 -d '127.0.0.1:34568/generated_code' to return the original url
   
2. From browser:
   type in your browser tiny url "127.0.0.1:34568/generated_code" and you will be redirected to the oridinal url 'www.your_url.xxx'

