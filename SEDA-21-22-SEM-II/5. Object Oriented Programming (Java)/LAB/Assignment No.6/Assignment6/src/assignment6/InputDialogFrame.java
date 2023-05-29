package assignment6;


import java.awt.Color;
import javax.swing.JFrame;
import javax.swing.JOptionPane;

public class InputDialogFrame extends JFrame{

    /**
	 * 
	 */
	//private static final long serialVersionUID = 1L;

	public InputDialogFrame() {

        getContentPane().setBackground(Color.DARK_GRAY);
        setTitle("Input Dialog in Frame");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
        setResizable(false);
        setSize(400, 300);
        getContentPane().setLayout(null);

    }
  void closeIt(){

        this.getContentPane().setVisible(false);
        this.dispose();

    }
}

