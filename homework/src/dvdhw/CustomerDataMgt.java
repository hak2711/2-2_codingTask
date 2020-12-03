package dvdhw;

import java.util.Vector;

/*
 * 1917017 박현아
 * 
 *  DataMgt를 상속받은 클래스. 제네릭 타입을 Customer로 지정하고 추상메소드 두 개 override함.
 *  
 * */
public class CustomerDataMgt extends DataMgt<Customer> {
	private Vector<Customer> collect;

	public CustomerDataMgt() { // 생성자
		collect = getCollect();
	}

	@Override
	public Customer selectByName(String name) {
		int slength = name.length();

		if (slength == 1) { // 성씨가 입력된 경우
			String lastname;
			for (Customer obj : collect) { // Vector에 저장된 고객 중 이름이 일치하는 고객 있다면 리턴해줌. 없으면 null 리턴.
				lastname = obj.getName().substring(0,1);
				if (name.equals(lastname)) {
					return obj;
				}
			}
			return null;
		}

		else if (slength == 2) { // 이름이 입력된 경우
			String firstname;
			for (Customer obj : collect) { // Vector에 저장된 고객 중 이름이 일치하는 고객 있다면 리턴해줌. 없으면 null 리턴.
				firstname = obj.getName().substring(1, 3);
				if (name.equals(firstname)) {
					return obj;
				}
			}
			return null;
		}

		else {
			String fullname;
			for (Customer obj : collect) { // Vector에 저장된 고객 중 이름이 일치하는 고객 있다면 리턴해줌. 없으면 null 리턴.
				fullname = obj.getName();
				if (name.equals(fullname)) {
					return obj;
				}
			}
			return null;
		}
	}

	@Override
	public Customer selectById(String id) {
		for (Customer obj : collect) { // Vector에 저장된 고객 중 id가 일치하는 고객이 있다면 리턴해줌. 없으면 null 리턴.
			if (id.equals(obj.getLoginId())) {
				return obj;
			}
		}

		return null;
	}

}
