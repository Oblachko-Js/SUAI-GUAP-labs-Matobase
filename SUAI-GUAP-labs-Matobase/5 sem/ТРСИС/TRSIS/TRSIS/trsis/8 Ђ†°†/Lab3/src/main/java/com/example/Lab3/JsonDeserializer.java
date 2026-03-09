package com.example.Lab3;

import com.fasterxml.jackson.databind.ObjectMapper;
import org.apache.kafka.common.header.Headers;
import org.apache.kafka.common.serialization.Deserializer;
import org.hibernate.type.SerializationException;

import java.io.ByteArrayInputStream;
import java.util.Map;

public class JsonDeserializer<T> implements Deserializer<T> {
    private final ObjectMapper objectMapper = new ObjectMapper();
    @Override
    public void configure(Map<String, ?> configs, boolean isKey) {}

//    @Override
//    public T deserialize(String s, byte[] bytes) {
//        return null;
//    }

    @Override
    public T deserialize(String s, byte[] bytes) {
        if(bytes == null) {
            return null;
        }
        try{
            return (T) objectMapper.readTree(new ByteArrayInputStream(bytes));
        }catch(Exception e){
            throw new SerializationException("Error serializing JSON message",e);
        }
    }

    @Override
    public T deserialize(String topic, Headers headers, byte[] data) {
        return Deserializer.super.deserialize(topic, headers, data);
    }

    @Override
    public void close() {
        Deserializer.super.close();
    }
}
