import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

@SuppressWarnings("serial")
public class LoginSystem extends JFrame implements ActionListener {
	WindowClass win;
	private JTextField[][] tf;
	private JLabel jlb1, jlb2, jlb3, jlb4, jlb5, jlb, danwei, jlb6, jlb7, jlb8,
			jlb9;
	private JButton jbt;
	private JPanel panel, panel1, panel2, panel3;
	int[][] Max;

	public LoginSystem() {
		setLayout(new BorderLayout());
		tf = new JTextField[6][3];
		Max = new int[6][3];
		jlb = new JLabel("�� �� �� ��");
		jlb1 = new JLabel("��        ��1");
		jlb2 = new JLabel("��        �� 2");
		jlb3 = new JLabel("��        ��3");
		jlb4 = new JLabel("��        ��4");
		jlb5 = new JLabel("��        ��5");
		jlb6 = new JLabel("ѡ��");
		jlb7 = new JLabel("�����");
		jlb8 = new JLabel("��Ԫ");
		jlb9 = new JLabel("ŷԪ");
		danwei = new JLabel("��λ(��)");
		jbt = new JButton("ȷ��");
		panel = new JPanel();
		panel1 = new JPanel();
		panel2 = new JPanel();
		panel3 = new JPanel();
		panel.setLayout(new GridLayout(6, 1));
		panel.add(jlb);
		panel.add(jlb1);
		panel.add(jlb2);
		panel.add(jlb3);
		panel.add(jlb4);
		panel.add(jlb5);
		panel2.setLayout(new FlowLayout(FlowLayout.CENTER, 50, 0));
		panel3.setLayout(new FlowLayout(FlowLayout.CENTER, 100, 0));
		panel2.add(jlb6);
		panel2.add(jlb7);
		panel2.add(jlb8);
		panel2.add(jlb9);
		panel3.add(danwei);
		panel3.add(jbt);
		jbt.addActionListener(this);
		this.getContentPane().add(panel, BorderLayout.WEST);
		panel1.setLayout(new GridLayout(6, 3));
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 3; j++) {
				tf[i][j] = new JTextField(5);
				panel1.add(tf[i][j]);
			}
		this.getContentPane().add(panel1, BorderLayout.CENTER);
		this.getContentPane().add(panel3, BorderLayout.SOUTH);
		this.getContentPane().add(panel2, BorderLayout.NORTH);
		this.setTitle("������");
		this.setLocation(500, 200);
		this.setSize(333, 270);
		this.setVisible(true);
		this.setResizable(false);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		if ("ȷ��".equals(e.getActionCommand())) {
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 3; j++) {
					Max[i][j] = Integer.valueOf(tf[i][j].getText());
				}
			}
			LoginSystem.this.dispose();
			win = new WindowClass(Max);
		}
	}
}