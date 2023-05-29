import java.util.*;
public class student {

    int contactNumber, registratoinId;
    String name, branch;
    static int  i;
    static {
        i = 1001;
    }

    student(String name, String branch, int contactNumber) {
        this.registratoinId = i;
        this.contactNumber = contactNumber;
        this.name = name;
        this.branch = branch;
        i++;
    }

    public void display()
    {
        System.out.println("Hi "+name+"! Your Registration ID is D"+registratoinId);
    }
    public static void main(String[] args) {
        student s1 = new student("Rohit","Computer", 1234567889);
        s1.display();
        student s2 = new student("Sayli","Mechanical", 1988612300);
        s2.display();
    }
}

