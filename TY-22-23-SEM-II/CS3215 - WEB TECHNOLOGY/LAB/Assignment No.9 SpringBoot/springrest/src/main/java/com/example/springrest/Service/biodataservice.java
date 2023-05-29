package com.springrest.springrest.services;
import com.springrest.springrest.entities.biodata;

import java.util.*;
public interface biodataservice {
    public List<biodata> getbiodata();

    public biodata getbiodatabyId(int id);

    public biodata addbiodata(biodata biodata);
}
