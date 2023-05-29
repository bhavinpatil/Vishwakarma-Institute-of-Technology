import java.util.Scanner;

public class Assignment4 {

    public static void main(String[] args) {
        int choice;

        Scanner sc = new Scanner(System.in);

        do {

            System.out.println("\n1. Arithmetic Exception\n2. ArrayIndexOutOfBounds Exception\n3. NullPointer Exception\n0. Exit\nEnter your choice");
            choice = sc.nextInt();
            switch (choice) {
                case 1:
                    int a, b;
                    System.out.println("Enter the first number: ");
                    a = sc.nextInt();
                    System.out.println("Enter the second number: ");
                    b = sc.nextInt();
                    try {
                        System.out.println("The answer is : " +a / b);
                    } catch (ArithmeticException e) {
                        System.out.println("You shouldn't divide the number by zero");
                    }
                    break;
                case 2:
                    int[] arr = { 10, 20, 30 };
                    int ind;
                    System.out.println("Enter the index for which the element is to be accessed");
                    ind = sc.nextInt();
                    try {
                        System.out.println("The element in the array at index " + ind + " is " + arr[ind]);
                    } catch (ArrayIndexOutOfBoundsException e) {
                        System.out.println("OOPs!!!Array Index " + ind + " out of bounds for length " + arr.length);
                    }
                    break;
                case 3:
                    String str = null;
                    try {
                        System.out.println(str.length());
                    } catch (NullPointerException e) {
                        System.out.println("Null Pointer Exception Arises as the string is null");
                    }
                    break;
                case 0:
                    break;
            }
        } while (choice != 0);
    }
}
