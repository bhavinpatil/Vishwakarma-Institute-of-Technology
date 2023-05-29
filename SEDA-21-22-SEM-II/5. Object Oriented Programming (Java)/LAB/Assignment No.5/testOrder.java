import java.util.*;

class Order {
    int orderNo;
    String[] itemNames;
    boolean status;

    Order(int orderNo, String[] itemNames, boolean status) {
        this.orderNo = orderNo;
        this.itemNames = itemNames;
        this.status = status;
    }

    public String[] getItems() {
        return itemNames;
    }
}

public class testOrder {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        ArrayList<Order> orders = new ArrayList<>();
        
        System.out.println("\n\nEnter no. of items for Order No. 1: ");
        int no = s.nextInt();

        String[] list1 = new String[no];
        System.out.println("\nEnter names of Items: ");
        for (int i = 0; i < no; i++) {
            list1[i] = s.next();
        }
        
        System.out.println("\n\nEnter no. of items for Order No. 2: ");
        no = s.nextInt();
        
        String[] list2 = new String[no];
        System.out.println("\nEnter names of Items: ");
        for (int i = 0; i < no; i++) {
            list2[i] = s.next();
        }
        
        System.out.println("\n\nEnter no. of items for Order No. 3: ");
        no = s.nextInt();
        
        String[] list3 = new String[no];
        System.out.println("\nEnter names of Items: ");
        for (int i = 0; i < no; i++) {
            list3[i] = s.next();
        }
        
        Order order1 = new Order(101, list1, true);
        Order order2 = new Order(102, list2, true);
        Order order3 = new Order(102, list3, true);

        orders.add(order1);
        orders.add(order2);
        orders.add(order3);

        Iterator<Order> o = orders.iterator();
        
        while (o.hasNext()) {
            Order obj = (Order) o.next();
            System.out.print(Arrays.toString(obj.getItems()));
        }
    }
}
