import javax.swing.*;
import java.awt.*;
import java.awt.event.*;


public class CalculatorGUI extends JFrame implements ActionListener {

    private JLabel firstPrompt;
    private JLabel secondPrompt;
    private JTextField firstNumber;
    private JTextField secondNumber;
    private JButton addButton;
    private JButton subtractButton;
    private JButton multiplyButton;
    private JButton divideButton;
    private JLabel resultLabel;

    public CalculatorGUI() {

        // initiate the GUI Components
        firstPrompt = new JLabel("First Number");
        secondPrompt = new JLabel("Second Number");
        firstNumber = new JTextField(25);
        secondNumber = new JTextField(25);
        addButton = new JButton("+");
        subtractButton = new JButton("-");
        multiplyButton = new JButton("*");
        divideButton = new JButton("/");
        resultLabel = new JLabel("Result:");

        // add the components
        setLayout(new FlowLayout(FlowLayout.LEFT));
        add(firstPrompt);
        add(firstNumber);
        add(secondPrompt);
        add(secondNumber);
        add(addButton);
        add(subtractButton);
        add(multiplyButton);
        add(divideButton);
        add(resultLabel);

        // make buttons clickable
        addButton.addActionListener(this);
        subtractButton.addActionListener(this);
        multiplyButton.addActionListener(this);
        divideButton.addActionListener(this);

        setSize(400, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        try {
            double num1 = Double.parseDouble(firstNumber.getText());
            double num2 = Double.parseDouble(secondNumber.getText());
            double result = 0;

            if (e.getSource() == addButton) {
                result = num1 + num2;
            } else if (e.getSource() == subtractButton) {
                result = num1 - num2;
            } else if (e.getSource() == multiplyButton) {
                result = num1 * num2;
            } else if (e.getSource() == divideButton) {
                if (num2 == 0) {
                    resultLabel.setText("Error: Division by zero");
                    return;
                } else {
                    result = num1 / num2;
                }
            }

            resultLabel.setText("Result: " + result);
        } catch (NumberFormatException ex) {
            resultLabel.setText("Error: Invalid input");
        }
    }
}
