# Описание
Это небольшая демка показывающая принципиальное устройство протоколов передачи информации между сервером и клиентом.
В данном случае передаются сообщения. У клиента и сервера они хранятся в виде объектов класса Message с полями типа int и std::string, с помощью метода to\_string() объект сериализуется в строку формата '\<id\>;\<from\>;\<to\>;\<text\>' после чего эта строка передается через tcp соединение на сервер и там десериализуется в объект класса Message.

# Пример работы
server:
```
Server listening on port 1278...
Connection accepted from 127.0.0.1:53568
Message from client: 10;Ivan;Sergey;Hello my dear friend
Response sent
```
client
```
Connected to server
exit? >no
id >10
from >Ivan
to >Sergey
text >Hello my dear friend
Message sent
Server response: Get message with id = 10 from Ivan to Sergey with text: Hello my dear friend
exit? >exit
```
