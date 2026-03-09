FROM docker pull eclipse-temurin:17.0.9_9-jdk
RUN mkdir -p /usr/src/myapp
COPY target/Lab3.jar /usr/src/myapp
RUN mkdir -p /usr/src/myapp/target
COPY target/keystore.p12 /usr/src/myapp/target
WORKDIR /usr/src/myapp
VOLUME /tmp
ARG JAR_FILE
ADD ${JAR_FILE} app.jar
ENTRYPOINT ["java","-jar","/Lab3.jar"]
