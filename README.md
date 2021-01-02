# TelegramBotCorona_Sensor

Thsi is the platformIO project for creating as small sensor for getting data



Use following sensors:

- SGP 30

- BME 280

For wifi you have to config the credentials at runtime. The server you have to change the CONNECTION_STRING with your REST-Server ip and port. It uses the interface from [Rest-Server](https://github.com/MrTarantoga/CoronaAir_SGP30_REST_Server).

Note:

The -3.0°C negative offset in the main.cpp is enclosure depending:![image](https://github.com/MrTarantoga/CoronaAir_Sensor/blob/main/enclosure.jpg)

The crossbar should prevent the heat transfer to the sensors. The added ventilation holes have to work as a gas exchange. 

![image](https://github.com/MrTarantoga/CoronaAir_Sensor/blob/main/enclosure.jpg)
