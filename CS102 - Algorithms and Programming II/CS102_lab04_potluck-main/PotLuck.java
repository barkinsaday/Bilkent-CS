import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.border.EmptyBorder;

/*
    @author: Barkın_Saday
    @project_name: Lab04
    @date: 25.11.2020
 */

public class PotLuck extends JFrame implements ActionListener {
    //properities
    int row;
    int column;
    int bomb1 = 0;
    int bomb2 = 0;
    int prize = 0;
    int counter = 0;

    JPanel content;
    JPanel panel;
    JLabel label;

    JButton prize_button;
    JButton bomb1_button;
    JButton bomb2_button;

    //consturactor
    PotLuck(int row, int column)
    {
        this.row = row;
        this.column = column;

        setTitle( "PotLuck Game!!!");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        content = new JPanel();
        content.setBorder(new EmptyBorder(row, row, column, column));
        content.setLayout(new BorderLayout(0, 0));
        setContentPane(content);

        panel = new JPanel();
        content.add(panel, BorderLayout.CENTER);
        panel.setLayout(new GridLayout(row, column, row*2, column*2));

        //to make sure bomb1, bomb2 and prize are not on the same button
        while (prize == bomb1 ||  prize == bomb2 ||bomb1 == bomb2)
        {
            prize = (int)(Math.random()*(row*column));
            bomb1 = (int)(Math.random()*(row*column));
            bomb2 = (int)(Math.random()*(row*column));
        }

        for(int i = 0; i < ( row * column ); i++){
            if(prize == i){
                prize_button = new JButton();
                prize_button.addActionListener(this);
                panel.add(prize_button);
            }
            else if  (bomb1 ==i ){
                bomb1_button = new JButton();
                bomb1_button.addActionListener(this);
                panel.add(bomb1_button);
            }
            else if  (bomb2 ==i ){
                bomb2_button = new JButton();
                bomb2_button.addActionListener(this);
                panel.add(bomb2_button);
            }
            else{
                JButton other_buttons = new JButton();
                panel.add(other_buttons);
                other_buttons.addActionListener(this);
            }
        }

        label = new JLabel("Total attempt: "+counter+" times\r\n");
        label.setHorizontalAlignment(SwingConstants.CENTER);
        content.add(label, BorderLayout.NORTH);
    }//end consturactor

    //Action Performed method,
    public void actionPerformed( ActionEvent myEvent)
    {
        if ( myEvent.getSource() != prize_button && myEvent.getSource() != bomb1_button && myEvent.getSource() != bomb2_button){
            counter ++;
            ((JButton) myEvent.getSource()).setEnabled(false);
            label.setText("Number of attempts: "+counter );
        }

        else if ( myEvent.getSource() == prize_button){
            label.setText("You got it in " + (counter + 1) + " attempts!" );
            for(int i = 0; i < ( row * column ); i++){
                if(panel.getComponent(i) != prize_button){
                    ((JButton) panel.getComponent(i)).setEnabled(false);
                }
            }
        }
        else {
            label.setText("The bomb is exploded!!! " + "Number of attempts " + (counter + 1));
            for(int i = 0; i < ( row * column ); i++){
                if(panel.getComponent(i) != prize_button|| panel.getComponent(i) != bomb1_button || panel.getComponent(i) != bomb2_button){
                    ((JButton) panel.getComponent(i)).setEnabled(false);
                }
            }
        }
    }
}//end class