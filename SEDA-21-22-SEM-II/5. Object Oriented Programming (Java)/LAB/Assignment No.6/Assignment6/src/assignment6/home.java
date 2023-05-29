package assignment6;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;

import java.awt.Font;
import javax.swing.JTextField;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;
import java.awt.event.ActionEvent;

public class home {

	private JFrame frame;
	private JTextField textField_roll;
	private JTextField textField_name;
	private JTextField textField_class;
	//String driverName = "com.mysql.jdbc.Driver";
    static final String DB_URL = "jdbc:mysql://localhost:3306/assignment6";
    static final String USER = "root";
    static final String PASS = "";

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					home window = new home();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public home() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		frame.setBounds(100, 100, 450, 300);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(null);
		
		JLabel lblNewLabel_roll = new JLabel("Roll No");
		lblNewLabel_roll.setFont(new Font("Tahoma", Font.BOLD, 12));
		lblNewLabel_roll.setBounds(90, 56, 43, 14);
		frame.getContentPane().add(lblNewLabel_roll);
		
		JLabel lblNewLabel = new JLabel("Student Login");
		lblNewLabel.setFont(new Font("Tahoma", Font.BOLD, 14));
		lblNewLabel.setBounds(165, 11, 111, 35);
		frame.getContentPane().add(lblNewLabel);
		
		textField_roll = new JTextField();
		textField_roll.setFont(new Font("Tahoma", Font.PLAIN, 12));
		textField_roll.setBounds(165, 53, 166, 20);
		frame.getContentPane().add(textField_roll);
		textField_roll.setColumns(10);
		
		JLabel lblNewLabel_name = new JLabel("Name:  ");
		lblNewLabel_name.setFont(new Font("Tahoma", Font.BOLD, 12));
		lblNewLabel_name.setBounds(90, 93, 46, 14);
		frame.getContentPane().add(lblNewLabel_name);
		
		textField_name = new JTextField();
		textField_name.setFont(new Font("Tahoma", Font.PLAIN, 12));
		textField_name.setBounds(165, 90, 166, 20);
		frame.getContentPane().add(textField_name);
		textField_name.setColumns(10);
		
		JLabel lblNewLabel_class = new JLabel("Marks");
		lblNewLabel_class.setFont(new Font("Tahoma", Font.BOLD, 12));
		lblNewLabel_class.setBounds(90, 137, 46, 14);
		frame.getContentPane().add(lblNewLabel_class);
		
		textField_class = new JTextField();
		textField_class.setBounds(165, 135, 166, 20);
		frame.getContentPane().add(textField_class);
		textField_class.setColumns(10);
		
		JButton btnNewButton = new JButton("ADD");
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				    String roll = textField_roll.getText();
	                String sName = textField_name.getText();
	                String class1 = textField_class.getText();
       try {
	                  Class.forName("com.mysql.jdbc.Driver");
	                   Connection connection = DriverManager.getConnection(DB_URL,USER,PASS);
	                   String query = "INSERT INTO student values('" + roll + "','" + sName + "','" + class1 + "')";
	                   Statement sta = connection.createStatement();
	                   int x = sta.executeUpdate(query);
	                    
	                        JOptionPane.showMessageDialog(btnNewButton,"data for "+ sName + " added sucessfully ");
	                    
	                    connection.close();
	                } catch (Exception exception) {
	                    exception.printStackTrace();
	                }
	            }
			
		});
		
		btnNewButton.setFont(new Font("Tahoma", Font.BOLD, 13));
		btnNewButton.setBounds(28, 201, 89, 23);
		frame.getContentPane().add(btnNewButton);
		
		JButton btnDisplay = new JButton("DISPLAY");
		btnDisplay.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				new display().showTableData();
			}
		});
		btnDisplay.setFont(new Font("Tahoma", Font.BOLD, 13));
		btnDisplay.setBounds(127, 201, 109, 23);
		frame.getContentPane().add(btnDisplay);
		
		JButton btnUpdate = new JButton("UPDATE");
		btnUpdate.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				new update().updateTableData();
				
			}
		});
		btnUpdate.setFont(new Font("Tahoma", Font.BOLD, 13));
		btnUpdate.setBounds(246, 201, 89, 23);
		frame.getContentPane().add(btnUpdate);
		
		JButton btnDelete = new JButton("DELETE");
		btnDelete.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				new delete().deleteTableData();
			}
		});
		btnDelete.setFont(new Font("Tahoma", Font.BOLD, 13));
		btnDelete.setBounds(345, 201, 89, 23);
		frame.getContentPane().add(btnDelete);
	}
}
