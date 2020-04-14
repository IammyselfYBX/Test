import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

@SuppressWarnings("serial")
public class WindowClass extends JFrame {
	final JTextArea jta1 = new JTextArea(20, 20);
	final JTextArea jta2 = new JTextArea(20, 20);
	static LoginSystem ls;
	JPanel p1 = new JPanel(new FlowLayout(50, 30, 10));
	JPanel p2 = new JPanel(new GridLayout(1, 2, 10, 10));
	int[][] Max;

	public static void main(String[] args) {
		ls = new LoginSystem();
		ls.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}

	public WindowClass() {
	}

	public WindowClass(int jf[][]) {
		Max = new int[6][3];// 进程完成需要的最大资源
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 3; j++) {
				Max[i][j] = jf[i][j];
				// System.out.println(Max[i][j]+" ");
			}
		this.setLayout(new BorderLayout());
		final JButton jbt = new JButton("开始工作");
		this.add(p1, BorderLayout.NORTH);
		p1.setBackground(Color.orange);
		this.add(p2, BorderLayout.SOUTH);
		p1.add(jbt);
		jbt.setBackground(Color.magenta);
		jbt.addActionListener(new BankClass());
		p2.setBackground(Color.BLACK);
		p2.add(jta1);
		jta1.setBackground(Color.pink);
		p2.add(jta2);
		jta2.setBackground(Color.lightGray);
		this.setTitle("银行系统");
		this.setBounds(100, 100, 600, 450);
		this.setVisible(true);
		getContentPane().add(new JScrollPane(p2));
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}

	class BankClass implements ActionListener {
		int a = 0;
		ConsumerClass consumer;
		
		@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			consumer = new ConsumerClass(Max);
			new Thread(consumer).start();
		}
	}

	class ConsumerClass implements Runnable {
		int[][] max;
		int[] Available, Available1;
		int[][] Allocation, Need;//进程当前已经得到的资源
		int[][] Allocation1, Need1;
		int a = 1;
		boolean[] Sos = new boolean[5];
		boolean[] sort;

		public ConsumerClass(int[][] jf) {
			max = new int[5][3];
			Allocation = new int[5][3];
			Allocation1 = new int[5][3];
			Available = new int[3];// 系统剩余资源
			Need1 = new int[5][3];// 本次系统需要的资源
			Available1 = new int[3];// 系统剩余资源
			Need = new int[5][3];// 本次系统需要的资源
			Available[0] = jf[0][0];
			Available[1] = jf[0][1];
			Available[2] = jf[0][2];
			Available1[0] = jf[0][0];
			Available1[1] = jf[0][1];
			Available1[2] = jf[0][2];
			sort = new boolean[5];
			for (int i = 0; i < 5; i++) {
				sort[i] = true;
				Sos[i] = true;
			}
			for (int i = 1; i < 6; i++)
				for (int j = 0; j < 3; j++) {
					max[i - 1][j] = jf[i][j];
					Need[i - 1][j] = jf[i][j];
					Need1[i - 1][j] = jf[i][j];
				}
		}

		@Override
		public void run() {

			int[] Request = new int[3];
			jta1.append("客" + "        " + "户" + "        " + "窗" + "        "
					+ "口" + "\n");
			jta2.append("银" + "        " + "行" + "        " + "窗" + "        "
					+ "口" + "\n");
			// TODO Auto-generated method stub
			while (a < 6) {
				if (sort[a - 1] = true) {
					Request = Sort();// 客户开始申请资源
					jta1.append("客户" + a + "进入银行取款" + "     " + "取款金额为："
							+ Request[0] + " " + Request[1] + " " + Request[2]
							+ "\n");
					jta2.append("正在进行安全性检查，请稍等..." + "\n");
					if (check(Request)) {
						CapitalSet(Request);// 安全状态通过，则修改数值
						try {
							if (true) {
								Thread.sleep(100);
								jta1.append("客户" + a + "取到了钱" + "\n");
								jta1.append("人民币：" + Request[0] + "美元："
										+ Request[1] + "欧元：" + Request[2]
										+ "         " + "还需要的取款金额为："
										+ Need[a - 1][0] + " " + Need[a - 1][1]
										+ " " + Need[a - 1][2] + "\n");
								jta2.append("银行此时剩余金额为:" + Available[0] + " "
										+ Available[1] + " " + Available[2]
										+ "\n");
							}
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
					} else {
						jta1.append("经过安全检查,客户" + a + "取款金额不符合条件，所以禁止！" + "\n");
						jta2.append("银行此时剩余金额为:" + Available[0] + " "
								+ Available[1] + " " + Available[2] + "\n");
					}
					a++;
				} else {
					a++;
				}
				if (a == 6) {
					a = 1;
				}

				int c = 0;
				int[] tu = new int[5];
				for (int i = 0; i < 5; i++) {
					tu[i] = 0;
				}
				while (c < 5) {
					if (Need[c][0] == 0 && Need[c][1] == 0 && Need[c][2] == 0) {
						tu[c] = 1;
					}
					c = c + 1;
				}
				if (tu[0] == 1 && tu[1] == 1 && tu[2] == 1 && tu[3] == 1
						&& tu[4] == 1) {
					jta1.append("客户取款全部结束！！！！！！！！！！！！！！！");
					jta2.append("客户取款全部结束！！！！！！！！！！！！！！！");
					break;
				} else {
				}
				/*
				 * if(Need[0][0]==0&&Need[0][1]==0&&Need[0][2]==0&&
				 * Need[1][0]==0&&Need[1][1]==0&&Need[1][2]==0&&
				 * Need[2][0]==0&&Need[2][1]==0&&Need[2][2]==0&&
				 * Need[3][0]==0&&Need[3][1]==0&&Need[3][2]==0&&
				 * Need[4][0]==0&&Need[4][1]==0&&Need[4][2]==0){
				 * jta2.append("客户取款全部结束！！！！！！"); break;} else {}
				 */
			}
		}

		public int[] Sort() {
			int[] R = new int[3];
			for (int i = 0; i < 3; i++) {
				R[i] = (int) (Math.random() * 3);
			}
			return R;
		}

		public boolean check(int[] R) {
			boolean[] sos = new boolean[5];
			for (int i = 0; i < 5; i++) {
				sos[i] = true;
			}
			int b = 0;
			boolean c = true;
			if (a == 1) {
				if (Need1[a - 1][0] >= R[0] && Need1[a - 1][1] >= R[1]
						&& Need1[a - 1][2] >= R[2] && R[0] <= Available1[0]
						&& R[1] <= Available1[1] && R[2] <= Available1[2]
						&& Available1[0] >= 0 && Available1[1] >= 0
						&& Available1[2] >= 0) {
					for (int i = 0; i < 3; i++) {
						Need1[a - 1][i] = Need1[a - 1][i] - R[i];
						Available1[i] = Available1[i] - R[i];
						Allocation1[a - 1][i] = Allocation1[a - 1][i] + R[i];
					}
					if (Need1[a - 1][0] == 0 && Need1[a - 1][1] == 0
							&& Need1[a - 1][2] == 0) {
						if (sos[a - 1] == true) {
							for (int i = 0; i < 3; i++) {
								Available1[i] = Available1[i] + max[a - 1][i];
							}
							sos[a - 1] = false;
						}
					}
					while (b < 5) {
						if (Available1[0] >= Need1[b][0]
								&& Available1[0] >= Need1[b][1]
								&& Available1[0] >= Need1[b][2]) {
							c = true;
						} else {
							c = false;
							break;
						}
						b++;
					}
				} else {
					c = false;
				}
			} else if (a == 2) {
				if (Need1[a - 1][0] >= R[0] && Need1[a - 1][1] >= R[1]
						&& Need1[a - 1][2] >= R[2] && R[0] <= Available1[0]
						&& R[1] <= Available1[1] && R[2] <= Available1[2]
						&& Available1[0] >= 0 && Available1[1] >= 0
						&& Available1[2] >= 0) {
					for (int i = 0; i < 3; i++) {
						Need1[a - 1][i] = Need1[a - 1][i] - R[i];
						Available1[i] = Available1[i] - R[i];
						Allocation1[a - 1][i] = Allocation1[a - 1][i] + R[i];
					}
					if (Need1[a - 1][0] == 0 && Need1[a - 1][1] == 0
							&& Need1[a - 1][2] == 0) {
						if (sos[a - 1] == true) {
							for (int i = 0; i < 3; i++) {
								Available1[i] = Available1[i] + max[a - 1][i];
							}
							sos[a - 1] = false;
						}
					}
					while (b < 5) {
						if (Available1[0] >= Need1[b][0]
								&& Available1[0] >= Need1[b][1]
								&& Available1[0] >= Need1[b][2]) {
							c = true;
						} else {
							c = false;
							break;
						}
						b++;
					}
				} else {
					c = false;
				}
			} else if (a == 3) {
				if (Need1[a - 1][0] >= R[0] && Need1[a - 1][1] >= R[1]
						&& Need1[a - 1][2] >= R[2] && R[0] <= Available1[0]
						&& R[1] <= Available1[1] && R[2] <= Available1[2]
						&& Available1[0] >= 0 && Available1[1] >= 0
						&& Available1[2] >= 0) {
					for (int i = 0; i < 3; i++) {
						Need1[a - 1][i] = Need1[a - 1][i] - R[i];
						Available1[i] = Available1[i] - R[i];
						Allocation1[a - 1][i] = Allocation1[a - 1][i] + R[i];
					}
					if (Need1[a - 1][0] == 0 && Need1[a - 1][1] == 0
							&& Need1[a - 1][2] == 0) {
						if (sos[a - 1] == true) {
							for (int i = 0; i < 3; i++) {
								Available1[i] = Available1[i] + max[a - 1][i];
							}
							sos[a - 1] = false;
						}
					}
					while (b < 5) {
						if (Available1[0] >= Need1[b][0]
								&& Available1[0] >= Need1[b][1]
								&& Available1[0] >= Need1[b][2]) {
							c = true;
						} else {
							c = false;
							break;
						}
						b++;
					}
				} else {
					c = false;
				}
			} else if (a == 4) {
				if (Need1[a - 1][0] >= R[0] && Need1[a - 1][1] >= R[1]
						&& Need1[a - 1][2] >= R[2] && R[0] <= Available1[0]
						&& R[1] <= Available1[1] && R[2] <= Available1[2]
						&& Available1[0] >= 0 && Available1[1] >= 0
						&& Available1[2] >= 0) {
					for (int i = 0; i < 3; i++) {
						Need1[a - 1][i] = Need1[a - 1][i] - R[i];
						Available1[i] = Available1[i] - R[i];
						Allocation1[a - 1][i] = Allocation1[a - 1][i] + R[i];
					}
					if (Need1[a - 1][0] == 0 && Need1[a - 1][1] == 0
							&& Need1[a - 1][2] == 0) {
						if (sos[a - 1] == true) {
							for (int i = 0; i < 3; i++) {
								Available1[i] = Available1[i] + max[a - 1][i];
							}
							sos[a - 1] = false;
						}
					}
					while (b < 5) {
						if (Available1[0] >= Need1[b][0]
								&& Available1[0] >= Need1[b][1]
								&& Available1[0] >= Need1[b][2]) {
							c = true;
						} else {
							c = false;
							break;
						}
						b++;
					}
				} else {
					c = false;
				}
			} else if (a == 5) {
				if (Need1[a - 1][0] >= R[0] && Need1[a - 1][1] >= R[1]
						&& Need1[a - 1][2] >= R[2] && R[0] <= Available1[0]
						&& R[1] <= Available1[1] && R[2] <= Available1[2]
						&& Available1[0] >= 0 && Available1[1] >= 0
						&& Available1[2] >= 0) {
					for (int i = 0; i < 3; i++) {
						Need1[a - 1][i] = Need1[a - 1][i] - R[i];
						Available1[i] = Available1[i] - R[i];
						Allocation1[a - 1][i] = Allocation1[a - 1][i] + R[i];
					}
					if (Need1[a - 1][0] == 0 && Need1[a - 1][1] == 0
							&& Need1[a - 1][2] == 0) {
						if (sos[a - 1] == true) {
							for (int i = 0; i < 3; i++) {
								Available1[i] = Available1[i] + max[a - 1][i];
							}
							sos[a - 1] = false;
						}
					}
					while (b < 5) {
						if (Available1[0] >= Need1[b][0]
								&& Available1[0] >= Need1[b][1]
								&& Available1[0] >= Need1[b][2]) {
							c = true;
						} else {
							c = false;
							break;
						}
						b++;
					}
				} else {
					c = false;
				}
			}
			return c;
		}

		public boolean index(int j) {
			return Sos[j];
		}

		public void Setindex(int i) {
			Sos[i] = false;
		}

		public void CapitalSet(int[] request) {
			// TODO Auto-generated method stub
			// boolean[] Sos=new boolean[5];
			if (a == 1) {
				for (int i = 0; i < 3; i++) {
					Need[a - 1][i] = Need[a - 1][i] - request[i];
					Available[i] = Available[i] - request[i];
					Allocation[a - 1][i] = Allocation[a - 1][i] + request[i];
				}
				if (Need[a - 1][0] == 0 && Need[a - 1][1] == 0
						&& Need[a - 1][2] == 0) {
					sort[a - 1] = false;
					if (index(a - 1)) {
						for (int i = 0; i < 3; i++) {
							Available[i] = Available[i] + max[a - 1][i];
						}
						Setindex(a - 1);
					}
				}
			} else if (a == 2) {
				for (int i = 0; i < 3; i++) {
					Need[a - 1][i] = Need[a - 1][i] - request[i];
					Available[i] = Available[i] - request[i];
					Allocation[a - 1][i] = Allocation[a - 1][i] + request[i];
				}
				if (Need[a - 1][0] == 0 && Need[a - 1][1] == 0
						&& Need[a - 1][2] == 0) {
					sort[a - 1] = false;
					if (index(a - 1)) {
						for (int i = 0; i < 3; i++) {
							Available[i] = Available[i] + max[a - 1][i];
						}
						Setindex(a - 1);
					}
				}
			} else if (a == 3) {
				for (int i = 0; i < 3; i++) {
					Need[a - 1][i] = Need[a - 1][i] - request[i];
					Available[i] = Available[i] - request[i];
					Allocation[a - 1][i] = Allocation[a - 1][i] + request[i];
				}
				if (Need[a - 1][0] == 0 && Need[a - 1][1] == 0
						&& Need[a - 1][2] == 0) {
					sort[a - 1] = false;
					if (index(a - 1)) {
						for (int i = 0; i < 3; i++) {
							Available[i] = Available[i] + max[a - 1][i];
						}
						Setindex(a - 1);
					}
				}
			} else if (a == 4) {
				for (int i = 0; i < 3; i++) {
					Need[a - 1][i] = Need[a - 1][i] - request[i];
					Available[i] = Available[i] - request[i];
					Allocation[a - 1][i] = Allocation[a - 1][i] + request[i];
				}
				if (Need[a - 1][0] == 0 && Need[a - 1][1] == 0
						&& Need[a - 1][2] == 0) {
					sort[a - 1] = false;
					if (index(a - 1)) {
						for (int i = 0; i < 3; i++) {
							Available[i] = Available[i] + max[a - 1][i];
						}
						Setindex(a - 1);
					}
				}
			} else if (a == 5) {
				for (int i = 0; i < 3; i++) {
					Need[a - 1][i] = Need[a - 1][i] - request[i];
					Available[i] = Available[i] - request[i];
					Allocation[a - 1][i] = Allocation[a - 1][i] + request[i];
				}
				if (Need[a - 1][0] == 0 && Need[a - 1][1] == 0
						&& Need[a - 1][2] == 0) {
					sort[a - 1] = false;
					if (index(a - 1)) {
						for (int i = 0; i < 3; i++) {
							Available[i] = Available[i] + max[a - 1][i];
						}
						Setindex(a - 1);
					}
				}
			}
		}
	}
}
