package dvdhw;

/*
 * 1917017 박현아
 * 
 * Person class를 상속받음.
 * 손님의 ID와 주소, 전화번호를 추가적으로 저장.
 * getter를 사용해 필드 정보에 접근.
 * toString으로 이름, 나이, 아이디, 주소, 전화번호 출력  
 * 
 * */
public class Customer extends Person {
	private String loginId;
	private String address;
	private String phoneNumber;

	public Customer(String name, int birthyear, String loginId, String address, String phoneNumber) {
		super(name, birthyear); // 슈퍼클래스 생성자 활용

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
		return super.toString() + "아이디:" + loginId + " 주소:" + address + " 전화번호:" + phoneNumber;
	}
}
