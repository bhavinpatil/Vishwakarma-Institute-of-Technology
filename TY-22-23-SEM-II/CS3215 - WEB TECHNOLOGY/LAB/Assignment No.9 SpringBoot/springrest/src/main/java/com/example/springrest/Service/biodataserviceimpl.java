package com.springrest.springrest.services;

import com.springrest.springrest.entities.biodata;
import org.springframework.stereotype.Service;
import java.util.*;

@Service
public class biodataserviceimpl implements biodataservice {

    List<biodata> list;

    public biodataserviceimpl()
    {
        list = new ArrayList<>();
        list.add(new biodata(1,"Mohit","Bahadure",22));
        list.add(new biodata(2,"Arpit","Bahadure",20));
    }

    @Override
    public List<biodata> getbiodata() {
        return list;
    }

    @Override
    public biodata getbiodatabyId(int id) {
        // TODO Auto-generated method stub
        biodata biodata = null;

        for (biodata data : list) {
            if (data.getId() == id) {
                biodata = data;
            }
        }
        return biodata;
    }

    @Override
    public biodata addbiodata(biodata biodata) {
        list.add(biodata);
        return biodata;
    }
}
