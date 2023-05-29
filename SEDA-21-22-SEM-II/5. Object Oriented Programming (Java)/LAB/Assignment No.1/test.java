public class Participants {
	int counter;
	static int registrationId;
	String name;
	long contactNumber;
	String branch;
	static {
		registrationId =1000;
	}
	
	public String getName() {
        return name;
    }

    public String getBranch() {
        return branch;
    }

    public long getCnumber() {
        return contactNumber;
    }
	public Participants(String name, long contactNumber, String branch) {
		this.name = name;
		this.contactNumber = contactNumber;
//		this.counter = registrationId;
		registrationId = registrationId+1;
	}
	void disp() {
		System.out.println("Hi " + name +"! "+ "Your registration id is D"+ registrationId);
	}

	public static void main(String []args) {
		Participants p = new Participants("Manasi", 917227, "CS");
		p.disp();
		Participants p2 = new Participants("Raj", 9174227, "EE");
		p2.disp();
	}
}