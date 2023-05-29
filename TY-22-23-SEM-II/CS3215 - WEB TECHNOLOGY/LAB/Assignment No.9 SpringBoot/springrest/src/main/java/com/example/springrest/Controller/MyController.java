package com.springrest.springrest.controller;
import com.springrest.springrest.entities.biodata;
import com.springrest.springrest.services.biodataservice;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RestController;
import java.util.*;
@RestController
public class MyController {
@Autowired
 private biodataservice bioservice;
    @GetMapping("/home")
    public String home() {
        return "This is home";
    }

    @GetMapping("/biodata")
    public List<biodata> getbioData()
    {
        return bioservice.getbiodata();
    }

    @GetMapping("/biodata/{id}")
    public biodata getbioDatabyId(@PathVariable int id)
    {
        return this.bioservice.getbiodatabyId(id);
    }

    @PostMapping("/biodata")
    public biodata addbiodata(@RequestBody biodata biodata)
    {
        return this.bioservice.addbiodata(biodata);
    }
}