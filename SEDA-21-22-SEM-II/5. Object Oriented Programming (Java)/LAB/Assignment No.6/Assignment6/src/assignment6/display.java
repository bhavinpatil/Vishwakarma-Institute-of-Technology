package assignment6;

import java.awt.BorderLayout;
import java.sql.*;
	import java.sql.Connection;
	import java.sql.DriverManager;
	import java.sql.ResultSet;
	import java.sql.Statement;

	import javax.swing.JFrame;
	import javax.swing.JOptionPane;
	import javax.swing.JScrollPane;
	import javax.swing.JTable;
	import javax.swing.table.DefaultTableModel;

	//import com.mysql.jdbc.PreparedStatement;

public class display {
	
	
		//String driverName = "com.mysql.jdbc.Driver";
	    static final String DB_URL = "jdbc:mysql://localhost:3306/assignment6";
	    static final String USER = "root";
	    static final String PASS = "";
		 public void showTableData() {

	  	   JFrame frame1 = new JFrame("Database Result");
	         JTable table;
	         PreparedStatement pst;
	         String[] columnNames = {"Roll No","Student Name" ,"Marks"};

		        frame1.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		        frame1.setLayout(new BorderLayout());
		        DefaultTableModel model = new DefaultTableModel();

		        model.setColumnIdentifiers(columnNames);

		        table = new JTable();

		        table.setModel(model);

		        table.setAutoResizeMode(JTable.AUTO_RESIZE_ALL_COLUMNS);

		        table.setFillsViewportHeight(true);

		        JScrollPane scroll = new JScrollPane(table);

		        scroll.setHorizontalScrollBarPolicy(

		                JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

		        scroll.setVerticalScrollBarPolicy(

		                JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);

		        try {
		        	//Class.forName(driverName); 
		        	Connection con = DriverManager.getConnection(DB_URL,USER,PASS);
		        	String sql = "select * from student";
		        	Statement ps =  con.createStatement();
		        	ResultSet rs = ps.executeQuery(sql);

		            int i = 0;
		            while(rs.next()) 
		           {
		            	int roll = rs.getInt(1);
		            	String sname =rs.getString(2);
		            	String class1 =rs.getString(3);
		            	
		                model.addRow(new Object[]{roll,sname,class1 });
		               i++;	
		            }
		            if(i <1)
		           {
		            	JOptionPane.showMessageDialog(null, "No Record Found","Error",
		            	JOptionPane.ERROR_MESSAGE);
		            	}
		            	if(i ==1)
		            	{
		            	System.out.println(i+" Record Found");
		            	}
		            	else
		            	{
		            	System.out.println(i+" Records Found");
		            	}
		            	
		        } catch (Exception ex) {
		            JOptionPane.showMessageDialog(null, ex.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
		        }
		       frame1.add(scroll);
		        frame1.setVisible(true);
		        frame1.setSize(400,300);
	  }
	  
	}

