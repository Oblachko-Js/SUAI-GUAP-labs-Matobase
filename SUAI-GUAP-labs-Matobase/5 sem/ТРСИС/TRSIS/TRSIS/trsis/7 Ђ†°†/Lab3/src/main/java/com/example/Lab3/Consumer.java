package com.example.Lab3;

import com.google.gson.Gson;
import org.apache.kafka.clients.consumer.ConsumerRecord;
import org.apache.kafka.clients.consumer.ConsumerRecords;
import org.apache.kafka.clients.consumer.KafkaConsumer;

import java.util.Arrays;
import java.util.Properties;

public class Consumer {
    public static void main(String[] args) throws Exception {
        String topicName = "test";
        Properties props = new Properties();
        props.put("bootstrap.servers", "localhost:9092");
        props.put("group.id", "test");
        props.put("enable.auto.commit", "true");
        props.put("session.timeout.ms", "30000");
        props.put("key.deserializer", "org.apache.kafka.common.serialization.StringDeserializer");
        props.put("value.deserializer", JsonDeserializer.class);

        KafkaConsumer<String, Lesson> consumer = new KafkaConsumer<>(props);
        consumer.subscribe(Arrays.asList(topicName));
        System.out.println("Subscribed to topic" + topicName);
//        int counter = 0;
        while (true) {
//            if(counter % 100 == 0)
//                System.out.println("Размер базы данных" + DBHelper.getAllLessons().size());
//            ++counter;

            ConsumerRecords<String,Lesson> records = consumer.poll(1);
            for (ConsumerRecord<String, Lesson> record : records) {
                Gson gson = new Gson();
                Lesson lesson = gson.fromJson(String.valueOf(record.value()),Lesson.class);
//                DBHelper.addLesson(lesson);
                System.out.println(lesson);
//                System.out.println(record.value());
            }
        }
    }
}
