package com.ssafy.petpal.room.entity;

import com.ssafy.petpal.home.entity.Home;
import jakarta.persistence.*;
import lombok.Builder;
import lombok.Getter;
import lombok.NoArgsConstructor;

@Entity
@Table(name = "Rooms")
@NoArgsConstructor
@Getter
public class Room {


    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "room_id")
    private Long id;

    @Column(name = "room_name")
    private String roomName;

    @ManyToOne
    @JoinColumn(name = "home_id")
    public Home home;

    @Builder
    public Room(String roomName, Home home){
        this.roomName = roomName;
        this.home = home;
    }
}
