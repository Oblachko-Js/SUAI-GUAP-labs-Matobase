package com.example.lab5.security;

import com.example.lab5.domain.User;
import com.example.lab5.repositories.UsersRepository;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Component;

import java.util.Optional;

@Slf4j
@Component
public class UserDetailsServiceImpl implements UserDetailsService {
    private final UsersRepository usersRepository;

    @Autowired
    public UserDetailsServiceImpl(UsersRepository usersRepository) {
        this.usersRepository = usersRepository;
    }

    @Override
    public UserDetails loadUserByUsername(String s) throws UsernameNotFoundException {
        Optional<User> optionalUser = usersRepository.findByUsername(s);

        User user = optionalUser.orElseThrow(() -> {
            log.error(String.format("Cannot find User with username [%s] to authorize", s));
//            throw new UnauthorizedException(String.format("Cannot find User with username [%s] to authorize", s));
            return null;
        });

        return new UserDetailsImpl(user);
    }
}
