package com.example.Lab3;

import org.apache.kafka.clients.producer.KafkaProducer;
import org.apache.kafka.clients.producer.ProducerRecord;

import java.util.Properties;

public class Producer{
    public static void main(String[] args) throws Exception{
        String topicName = "test";
        Properties props = new Properties();
        props.put("bootstrap.servers","localhost:9092");
        props.put("enable.auto.commit","true");
        props.put("session.timeout.ms","30000");
        props.put("key.serializer","org.apache.kafka.common.serialization.StringSerializer");
        props.put("value.serializer", JsonSerializer.class);

        KafkaProducer<String,Lesson> producer = new KafkaProducer<>(props);
        for(int i=0;i<10;++i){
            Lesson les = new Lesson("4132","23-09","Ivanov","Physics",i+1);
            producer.send(new ProducerRecord<>(topicName,Integer.toString(i),les));
        }
        producer.close();
    }
}