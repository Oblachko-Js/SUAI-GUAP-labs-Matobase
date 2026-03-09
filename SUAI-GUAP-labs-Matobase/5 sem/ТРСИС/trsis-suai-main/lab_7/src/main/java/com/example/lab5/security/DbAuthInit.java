package com.example.lab5.security;

import com.example.lab5.domain.User;
import com.example.lab5.repositories.UsersRepository;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Component;

import java.util.List;

@Slf4j
@Component
public class DbAuthInit implements CommandLineRunner {
    private final UsersRepository usersRepository;
    private final PasswordEncoder passwordEncoder;

    @Autowired
    public DbAuthInit(UsersRepository usersRepository, PasswordEncoder passwordEncoder) {
        this.usersRepository = usersRepository;
        this.passwordEncoder = passwordEncoder;
    }

    @Override
    public void run(String... args) {
        List<User> existingUsers = (List<User>) usersRepository.findAll();
        long count = existingUsers.stream()
                .filter(u -> u.getUsername().equals("admin") || u.getUsername().equals("user"))
                .count();
        if (count == 2) {
            return;
        }

        User user = new User("user", passwordEncoder.encode("user"), "USER", "");
        User admin = new User("admin", passwordEncoder.encode("admin"), "ADMIN", "");
        List<User> users = List.of(user, admin);
        usersRepository.saveAll(users);
    }
}
