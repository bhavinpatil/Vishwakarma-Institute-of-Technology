import java.util.Scanner;
public class Assignment2 {
    int[] a;
    int n, sum;

    void getnum() {
        Scanner s = new Scanner(System.in);
        System.out.println("Enter Numbers of the Array Elements: ");
        n = s.nextInt();
        a = new int[n];
        System.out.println("Enter Elements in the Array:");
        for (int i = 0; i < n; i++) {
            a[i] = s.nextInt();
        }
        System.out.println("Enter the Target Sum: ");
        sum = s.nextInt();
    }

    void getsumnum() {
        for (int i = 0; i < n; i++) {   
            for (int j = i + 1; j < n; j++) {
                if (a[i] + a[j] == sum) {
                    System.out.println("[" + a[i] + "," + a[j] + "]");
                }
            }
        }
    }

    public static void main(String[] args) {
        Assignment2 sam = new Assignment2();
        sam.getnum();
        sam.getsumnum();
    }
}