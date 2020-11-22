package dvdhw;

import java.util.*;

/*
 * 1917017 박현아
 * 
 * 매니저 정보를 저장하고 있는 클래스
 * 매니저인지 확인하는 메소드 포함.
 * 
 * */

public class ManagerData {
	HashMap<String, String> managerInfo = new HashMap<String, String>();

	public ManagerData() {
		managerInfo.put("admin", "admin1234");
		managerInfo.put("manager", "manager1234");
	}

	public boolean isManager(String id, String pw) { // 매니저 정보와 일치하면  true, 불일치하면 false 반환
		for (String key : managerInfo.keySet()) {
			String value = managerInfo.get(key);
			if (key.equals(id) && value.equals(pw))
				return true;
		}

		return false;
	}
}
