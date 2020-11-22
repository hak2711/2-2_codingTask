package dvdhw;

import java.time.LocalDate;
/*
 * 1917017 ������
 * 
 * ������ ���� �����ִ� Ŭ����. �� ����, ���� ����, ���� ��¥, �ݳ� ��¥, �ݳ� ���� ����.
 * getter�� ����� �ʵ� ������ ����
 * toString ����� �� �̸�, ���� ����, ���� ��¥, �ݳ���¥(���� �ݳ����� �ʾҴٸ� �ݳ���) ���.
 * */
public class RentDvd{
	private Customer customer;
	private Dvd dvd;
	private LocalDate borrowDate;
	private LocalDate returnDate;
	private boolean isReturn = false;
	
	public RentDvd(Customer customer, Dvd dvd){ //���� ���� ������ �Ķ���ͷ� �ް� ���� ��¥�� �����ϴ� ������.
		this.customer = customer;
		this.dvd = dvd;
		borrowDate = LocalDate.now();
	}
	
	public void setReturn() { //���� ���� �ݳ��ϸ� �ݳ� ���θ� �ٲٰ� �ݳ� ��¥�� �����ϴ� �޼ҵ�.
		isReturn = true;
		returnDate = LocalDate.now();
	}

	public Customer getCustomer() {
		return customer;
	}

	public Dvd getDvd() {
		return dvd;
	}

	public boolean isReturn() {
		return isReturn;
	}

	@Override
	public String toString() {
		String name = customer.getName();
		String title = dvd.getTitle();
		
		String borrow = borrowDate.toString();
		
		String rtndate = "�뿩 ��";
		if(returnDate != null) rtndate = returnDate.toString(); //���� �ݳ��Ͽ� �ݳ���¥�� ����Ǿ� �ִ� ���.
		
		return "�� �̸�:" + name + " DVD ����:" + title + " �뿩 ��¥:" + borrowDate.toString()
		       + " �ݳ� ��¥:" + rtndate;  
	}
}
