package com.ssafy.petpal.home.entity;

import com.ssafy.petpal.object.entity.Appliance;
import com.ssafy.petpal.schedule.entity.Schedule;
import com.ssafy.petpal.user.entity.User;
import jakarta.persistence.*;
import lombok.Builder;
import lombok.Getter;
import lombok.NoArgsConstructor;
import org.springframework.data.annotation.CreatedDate;

import java.time.LocalDateTime;
import java.util.List;

@Entity
@Table(name = "Homes")
@Getter
@NoArgsConstructor
public class Home {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "home_id")
    private Long id;

    @ManyToOne
    @JoinColumn(name = "user_id")
    private User user;

    @Column(name = "home_nickname")
    private String homeNickname;

    @CreatedDate
    @Column(name = "home_created_at")
    private LocalDateTime createdAt;

    @OneToMany(mappedBy = "home")
    private List<Appliance> appliances;

    @OneToMany(mappedBy = "home")
    private List<Schedule> schedules;

    @Builder
    public Home(User user, String homeNickname){
        this.user = user;
        this.homeNickname = homeNickname;
    }
}
