package dvdhw;

import java.util.*;

/*
 * 1917017 ������
 * 
 * �Ŵ��� ������ �����ϰ� �ִ� Ŭ����
 * �Ŵ������� Ȯ���ϴ� �޼ҵ� ����.
 * 
 * */

public class ManagerData {
	HashMap<String, String> managerInfo = new HashMap<String, String>();

	public ManagerData() {
		managerInfo.put("admin", "admin1234");
		managerInfo.put("manager", "manager1234");
	}

	public boolean isManager(String id, String pw) { // �Ŵ��� ������ ��ġ�ϸ�  true, ����ġ�ϸ� false ��ȯ
		for (String key : managerInfo.keySet()) {
			String value = managerInfo.get(key);
			if (key.equals(id) && value.equals(pw))
				return true;
		}

		return false;
	}
}
