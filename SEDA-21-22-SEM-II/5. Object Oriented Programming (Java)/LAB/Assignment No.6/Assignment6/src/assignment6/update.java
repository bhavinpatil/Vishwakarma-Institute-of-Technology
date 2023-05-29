package assignment6;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.awt.*;
import javax.swing.JOptionPane;


public class update {
	//String driverName = "com.mysql.jdbc.Driver";
    static final String DB_URL = "jdbc:mysql://localhost:3306/assignment6";
    static final String USER = "root";
    static final String PASS = "";
	 public void updateTableData() {
	    	
	       try {
	    	  Connection conn = DriverManager.getConnection(DB_URL,USER,PASS);
	    	  InputDialogFrame frame = new InputDialogFrame();
	         String m1 = JOptionPane.showInputDialog(frame, "Enter rollNo to update a record");
	         if(m1.isEmpty()){
	             frame.closeIt();
	         } 
	         String m = JOptionPane.showInputDialog(frame, "New value for Student name");
	         if(m.isEmpty()){
	             frame.closeIt();
	         } 
	          String usql = "update student set Name=? WHERE RollNo =?";
	          java.sql.PreparedStatement pst = conn.prepareStatement(usql);
	          pst.setString(1,m);
	    	  pst.setString(2,m1);
	    	  pst.executeUpdate();
	    	 JOptionPane.showMessageDialog(null, "record updated");
	    	} catch (SQLException e ) {
	      JOptionPane.showMessageDialog(null, e);

	  }
  }}      

