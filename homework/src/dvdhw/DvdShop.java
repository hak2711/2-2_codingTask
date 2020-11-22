package dvdhw;

import java.util.Scanner;

/*
 * 1917017 ������
 * 
 * Dvd�� ������ �뿩���ִ� DvdShop Ŭ����.
 * �� ���� �����ڿ� ���� ���� ������, �뿩��� ������, �Ŵ��� ���� ���� �ʵ忡 ����.
 * �α��νõ�, ���α׷� ����, �޴� ���, �޴��� �ش��ϴ� ��� ������ �޼ҵ带 ����.
 * 
 * 
 * */
public class DvdShop {
	private static Scanner sc = new Scanner(System.in);

	private CustomerDataMgt customers = new CustomerDataMgt(); // ������ ����
	private DvdDataMgt dvds = new DvdDataMgt(); // ���� ���� ����
	private RentDvdDataMgt rentDvds = new RentDvdDataMgt(); // ���� �뿩 ���� ����
	private ManagerData manager = new ManagerData();

	public static void main(String[] args) {
		DvdShop dvdShop = new DvdShop();
		int i = 0;
		while (true) {
			if (dvdShop.loginTry()) { // �α��� �õ� ������ ���
				dvdShop.start(); // ���α׷� ����
				break;
			} else { // �α��� �õ� ������ ���
				if (i >= 2) { // �α��� �õ� ���� Ƚ���� 3���� �Ѿ�� ���α׷� ���� ����
					System.out.println("���α׷� ����.");
					break;
				} else {
					System.out.println("���̵� ���ų� ���̵� Ȥ�� ��й�ȣ�� ��ġ���� �ʽ��ϴ�. ���� �õ� Ƚ�� : " + (2 - i));
					i++;
				}
			}
		}
	}

	public boolean loginTry() { // �α��� �õ� �޼ҵ�
		System.out.print("���̵�� ��й�ȣ�� �Է��Ͻÿ� : ");
		String id = sc.next();
		String pw = sc.next();

		return manager.isManager(id, pw);
	}

	public void start() { // dvdshop ���α׷� ����
		decoConsole(true, "=");
		System.out.println("Hyunah DVD Shop"); // <== ������ �̸����� ������ �� (��: ����ȭ DVD Shop)
		decoConsole(false, "=");

		while (true) {
			System.out.println();

			int menu = showMenu(); // �޴� ��� �� ������� �޴� ������ �Է¹޾� ��ȯ��
			if (menu == 0)
				break; // 0�� �ԷµǸ� ����

			switch (menu) {
			case 1:
				newCustomer();
				break; // �ű԰���
			case 2:
				searchCustomer();
				break; // ���˻�
			case 3:
				customersShowAll();
				break; // ��ü���˻�
			case 4:
				deleteCustomer();
				break; // �� ����
			case 5:
				newDvd();
				break; // DVD ���
			case 6:
				searchDvd();
				break; // DVD �˻�
			case 7:
				dvdsShowAll();
				break; // DVD ��ü �˻�
			case 8:
				deleteDvd();
				break; // DVD ����
			case 9:
				rentDvd();
				break; // DVD �뿩
			case 10:
				returnDvd();
				break; // DVD �ݳ�
			case 11:
				rentDvdsShowAll();
				break; // �뿩�� DVD ��ü �˻�
			case 12:
				deleteReturnedDvds();
				break; // �ݳ� �Ϸ�� DVD ����
			}
		}

	}

	public static int showMenu() { // �޴� ����ϰ� ����ڿ��� �޴� �Է¹���.
		int menu = -1;

		while (true) { // �޴� ���
			System.out.println("============================= �޴� =============================");
			System.out.println("(0) ���� (1) �ű԰��� (2) ���˻� (3) ��ü���˻� (4) ������");
			System.out.println("_______________________________________________________________");
			System.out.println("(5) DVD ��� (6) DVD �˻� (7) DVD ��ü�˻�  (8) Dvd ����");
			System.out.println("_______________________________________________________________");
			System.out.println("(9) DVD �뿩 (10) DVD �ݳ� (11) �뿩 ��� ��ü�˻� (12) �뿩 ��� ��ü ����");
			System.out.println("_______________________________________________________________");

			System.out.print("�޴��� �����ϼ��� >> ");

			try {
				menu = Integer.parseInt(sc.next());
				if (0 > menu || menu > 12) // �޴� ��ȣ ���� ��� ���
					throw new OutofRangeException();
				else
					break;
			} catch (NumberFormatException e) { // ������� �Է��� ���ڰ� �ƴ� ���
				System.out.println("���ڸ� �Է��Ͻʽÿ�.");
			} catch (OutofRangeException e) { // ������� �Է��� �޴� ������ �ش����� �ʴ� ���
				System.out.println(e.getMessage());
			}

		}

		System.out.println();
		return menu;
	}

	public static void decoConsole(boolean pre, String deco) { // ���α׷� �ٹ̴� �޼ҵ�
		if (pre)
			System.out.println();

		for (int i = 0; i < 30; i++)
			System.out.print(deco);

		System.out.println();
		if (!pre)
			System.out.println();
	}

	private void customersShowAll() { // ��ü �� �˻�
		String str = customers.showAll();

		if (str == null) // �˻� ����� ���� ���
			System.out.println("�� �˻� ����� �����ϴ�.");
		else
			System.out.println(str);
	}

	private void dvdsShowAll() { // ��ü ���� �˻�
		String str = dvds.showAll();

		if (str == null) // �˻� ����� ���� ���
			System.out.println("Dvd �˻� ����� �����ϴ�.");
		else
			System.out.println(str);
	}

	private void rentDvdsShowAll() { // ��ü �뿩 ��� �˻�
		String str = rentDvds.showAll();

		if (str == null) // �˻� ����� ���� ���
			System.out.println("�뿩 ��� �˻� ����� �����ϴ�.");
		else
			System.out.println(str);
	}

	private void searchCustomer() { // Ư�� �� �˻�
		System.out.print("�˻��� �� �̸��� �Է¼��� >> ");

		String name = sc.next();
		Customer cust = customers.selectByName(name);

		if (cust == null) // �˻� ����� ���� ���
			System.out.println("�� ������ �����ϴ�.");
		else
			System.out.println("\n���>> " + cust.toString());

	}

	private void searchDvd() { // Ư�� ���� �˻�
		System.out.print("�˻��� Dvd ������ �Է¼��� >> ");

		String title = sc.next();
		Dvd dvd = dvds.selectByName(title);

		if (dvd == null) // �˻� ����� ���� ���
			System.out.println("Dvd ������ �����ϴ�.");
		else
			System.out.println("\n���>> " + dvd.toString());

	}

	private void deleteCustomer() { // Ư�� �� ����
		int num = 0;

		System.out.print("������ �� �̸��� �Է¼��� >> ");

		String name = sc.next();
		Customer cust = customers.selectByName(name);

		while (cust != null) { // �ش� �̸��� ���� �� ������ ��� �����ϰ� ������ �� ������ ī��Ʈ.
			customers.delete(cust);
			cust = customers.selectByName(name);
			num++;
		}

		System.out.println(num + "���� ���� �����Ǿ����ϴ�.");

	}

	private void deleteDvd() { // Ư�� ���� ����
		int num = 0;

		System.out.print("������ Dvd ������ �Է¼��� >> ");

		String name = sc.next();
		Dvd dvd = dvds.selectByName(name);

		while (dvd != null) { // �ش� ������ ���� ���� ������ ��� �����ϰ� ������ ���� ������ ī��Ʈ.
			dvds.delete(dvd);
			RentDvd rentdvd = rentDvds.selectByName(name);

			if (rentdvd != null) { // �ش� ������ ���� ���� �뿩 ��Ͽ� �����ϸ� �� ������ ����.
				rentDvds.delete(rentdvd);
			}
			dvd = dvds.selectByName(name);
			num++;
		}

		System.out.println(num + "���� Dvd�� �����Ǿ����ϴ�.");

	}

	private void deleteReturnedDvds() { // �ݳ� �Ϸ�� ���� ��� ����
		System.out.println(rentDvds.removeReturnedDvd() + "���� �ݳ� �Ϸ�� Dvd�� �����Ǿ����ϴ�.");
	}

	public void newCustomer() { // �ű� �� �߰�
		String name, id, addr, phone;
		int year;

		while (true) {
			System.out.println("�� ������ �Է��ϼ���(�̸�, ����, ���̵�, �ּ�, ��ȭ��ȣ ������ �Է�) >>");

			name = sc.next();
			year = sc.nextInt();
			id = sc.next();
			addr = sc.next();
			phone = sc.next();

			if (customers.selectById(id) != null) // ���̵� �ߺ��� ���
				System.out.println("�̹� �����ϴ� ���̵��Դϴ�. �ٽ� �Է��ϼ���.");

			else // ���̵� �ߺ����� ���� ���
				break;
		}

		Customer cust = new Customer(name, year, id, addr, phone);
		customers.add(cust);
		System.out.println("�ű� ���� ����߽��ϴ�.");
	}

	public void newDvd() { // ���ο� ���� ���
		String isbn, title, producer, contry;
		while (true) {
			System.out.println("Dvd ������ �Է��ϼ���(ISBN, ����, ������, ������, �帣(1.�׼�,2.�ڹ�,3.�θ�ƽ,4.���,5.��Ÿ) >>");

			sc.nextLine();
			isbn = sc.next();
			title = sc.next();
			producer = sc.next();
			contry = sc.next();

			if (dvds.selectById(isbn) != null)// ISBN�� �ߺ��Ǵ� ���
				System.out.println("�̹� �����ϴ� ISBN�Դϴ�. �ٽ� �Է��ϼ���.");
			else // ISBN�� �ߺ����� �ʴ� ���
				break;
		}

		Genre genre = Genre.ETC;
		int num = Integer.parseInt(sc.next()); // �帣 ����
		if (num == 1)
			genre = Genre.Action;
		else if (num == 2)
			genre = Genre.Comic;
		else if (num == 3)
			genre = Genre.Romantic;
		else if (num == 4)
			genre = Genre.Drama;
		else
			genre = Genre.ETC;

		Dvd dvd = new Dvd(isbn, title, new Person(producer), contry, genre);
		System.out.println("DVD�� ����߽��ϴ�.");
		dvds.add(dvd);
	}

	public void rentDvd() { // ���� �뿩
		System.out.print("�뿩�� ���ϴ� �� ���̵�� �뿩�� Dvd�� ISBN�� �Է��ϼ��� >> ");

		String id = sc.next();
		String isbn = sc.next();

		if ((rentDvds.selectById(isbn) != null) && (!rentDvds.selectById(isbn).isReturn())) // �뿩 ��Ͽ� �ְ� �ݳ��� ���°� �ƴ� ���
			System.out.println("�ٸ� ���� �뿩 ���� Dvd�Դϴ�.");

		else if (dvds.selectById(isbn) == null) // �ش� isbn�� ���� dvd�� ã�� �� ���� ���
			System.out.println("Dvd�� ã�� �� �����ϴ�.");

		else if (customers.selectById(id) == null) // �ش� id�� ���� ���� ã�� �� ���� ���
			System.out.println("���� ã�� �� �����ϴ�.");

		else { // �ٸ� ���� �뿩 ���� �ƴ� ���
			Customer cust = customers.selectById(id);
			Dvd dvd = dvds.selectById(isbn);

			RentDvd rentInfo = new RentDvd(cust, dvd);
			rentDvds.add(rentInfo);
			System.out.println("�뿩�� �Ϸ�Ǿ����ϴ�.");
		}
	}

	public void returnDvd() { // ���� �ݳ�
		System.out.print("�ݳ��� Dvd�� ISBN�� �Է��ϼ��� >> ");

		String isbn = sc.next();

		RentDvd rentDvd = rentDvds.selectById(isbn);

		if (rentDvd == null) // �뿩�� �� ���� ������ ���
			System.out.println("�ش� Dvd�� �뿩 ��Ͽ� �������� �ʽ��ϴ�.");

		else { // �뿩�� ������ ���
			rentDvd.setReturn();
			System.out.println("�ݳ��� �Ϸ�Ǿ����ϴ�.");
		}
	}
}
