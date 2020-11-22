package dvdhw;

/*
 * 1917017 ������
 * 
 * Person class�� ��ӹ���.
 * �մ��� ID�� �ּ�, ��ȭ��ȣ�� �߰������� ����.
 * getter�� ����� �ʵ� ������ ����.
 * toString���� �̸�, ����, ���̵�, �ּ�, ��ȭ��ȣ ���  
 * 
 * */
public class Customer extends Person {
	private String loginId;
	private String address;
	private String phoneNumber;

	public Customer(String name, int birthyear, String loginId, String address, String phoneNumber) {
		super(name, birthyear); // ����Ŭ���� ������ Ȱ��

		this.loginId = loginId;
		this.address = address;
		this.phoneNumber = phoneNumber;
	}

	public String getAddress() {
		return address;
	}

	public String getLoginId() {
		return loginId;
	}

	public String getPhoneNumber() {
		return phoneNumber;
	}

	@Override
	public String toString() {
		return super.toString() + "���̵�:" + loginId + " �ּ�:" + address + " ��ȭ��ȣ:" + phoneNumber;
	}
}
