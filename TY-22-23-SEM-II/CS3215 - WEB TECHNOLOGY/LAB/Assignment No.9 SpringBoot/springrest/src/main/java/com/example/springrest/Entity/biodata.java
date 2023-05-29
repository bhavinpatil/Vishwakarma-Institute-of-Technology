package com.springrest.springrest.entities;

public class biodata {
    private int id;
    private String fname;
    private String lname;
    private int age;
    public biodata() {
        super();
        // TODO Auto-generated constructor stub
    }
    public biodata(int id, String fname, String lname, int age) {
        super();
        this.id = id;
        this.fname = fname;
        this.lname = lname;
        this.age = age;
    }
    public int getId() {
        return id;
    }
    public void setId(int id) {
        this.id = id;
    }
    public String getFname() {
        return fname;
    }
    public void setFname(String fname) {
        this.fname = fname;
    }
    public String getLname() {
        return lname;
    }
    public void setLname(String lname) {
        this.lname = lname;
    }
    public int getAge() {
        return age;
    }
    public void setAge(int age) {
        this.age = age;
    }
    @Override
    public String toString() {
        return "Biodata [id=" + id + ", fname=" + fname + ", lname=" + lname + ", age=" + age + "]";
    }

}
