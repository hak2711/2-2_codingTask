package dvdhw;

import java.time.LocalDate;
/*
 * 1917017 박현아
 * 
 * 고객에게 디비디를 빌려주는 클래스. 고객 정보, 디비디 정보, 빌린 날짜, 반납 날짜, 반납 여부 저장.
 * getter를 사용해 필드 정보에 접근
 * toString 사용해 고객 이름, 디비디 제목, 빌린 날짜, 반납날짜(아직 반납하지 않았다면 반납중) 출력.
 * */
public class RentDvd{
	private Customer customer;
	private Dvd dvd;
	private LocalDate borrowDate;
	private LocalDate returnDate;
	private boolean isReturn = false;
	
	public RentDvd(Customer customer, Dvd dvd){ //고객과 디비디 정보를 파라미터로 받고 빌린 날짜를 지정하는 생성자.
		this.customer = customer;
		this.dvd = dvd;
		borrowDate = LocalDate.now();
	}
	
	public void setReturn() { //고객이 디비디를 반납하면 반납 여부를 바꾸고 반납 날짜를 저장하는 메소드.
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
		
		String rtndate = "대여 중";
		if(returnDate != null) rtndate = returnDate.toString(); //고객이 반납하여 반납날짜가 저장되어 있는 경우.
		
		return "고객 이름:" + name + " DVD 제목:" + title + " 대여 날짜:" + borrowDate.toString()
		       + " 반납 날짜:" + rtndate;  
	}
}
