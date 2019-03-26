package com.airplan.manager;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class AirplanManagerApplication {

	public static void main(String[] args) {
		System.out.println("Hello Spring !");
		SpringApplication.run(AirplanManagerApplication.class, args);
	}
	@RequestMapping("/")
	public String showMainPage(){
		return "Hello Spring";
	}
}
