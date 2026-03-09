package com.example.lab5.domain;

import lombok.*;

import javax.persistence.*;
import javax.validation.constraints.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

@Data
@Entity
@Table(name = "usr")
@EqualsAndHashCode(of = "id")
@NoArgsConstructor
@AllArgsConstructor
@RequiredArgsConstructor
public class User {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    @NotNull(message = "Id cannot be null")
    @Min(value = 0, message = "id cannot be less then 0")
    @Column(name = "id")
    private Long id;

    @NonNull
    @NotBlank(message = "This field cannot be blank")
    @Column(name = "username")
    private String username;

    @NonNull
    @NotBlank(message = "This field cannot be blank")
    @Size(min = 6, message = "Password should be at least 6 characters")
    @Column(name = "password")
    private String password;

    @Column(name = "roles")
    private String roles;

    @Column(name = "authorities")
    private String authorities;

    public User(@NonNull String username, @NonNull String password, String roles, String authorities) {
        this.username = username;
        this.password = password;
        this.roles = roles;
        this.authorities = authorities;
    }

    public List<String> getRoles() {
        if (roles.length() > 0) {
            return Arrays.asList(roles.split(","));
        }
        return new ArrayList<>();
    }

    public List<String> getAuthorities() {
        if (authorities.length() > 0) {
            return Arrays.asList(authorities.split(","));
        }
        return new ArrayList<>();
    }
}