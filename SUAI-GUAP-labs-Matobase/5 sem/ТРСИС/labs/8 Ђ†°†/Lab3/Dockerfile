#Базовый образ
FROM eclipse-temurin:17.0.9_9-jdk
#Необходимые директории
RUN mkdir -p /usr/src/myapp
#JAR-файл
COPY target/Lab3-0.0.1-SNAPSHOT.jar /usr/src/myapp/
COPY target/keystore.p12 /usr/src/myapp/target/
#Установка рабочей директории
WORKDIR /usr/src/myapp
#Том
VOLUME /tmp
#Установка JAR-файла как аргумента
ARG JAR_FILE=Lab3-0.0.1-SNAPSHOT.jar
# Запуск приложения
ENTRYPOINT ["java","-jar","/usr/src/myapp/Lab3-0.0.1-SNAPSHOT.jar"]
