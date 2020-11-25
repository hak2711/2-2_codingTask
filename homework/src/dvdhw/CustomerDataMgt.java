package dvdhw;

import java.util.Vector;

/*
 * 1917017 ������
 * 
 *  DataMgt�� ��ӹ��� Ŭ����. ���׸� Ÿ���� Customer�� �����ϰ� �߻�޼ҵ� �� �� override��.
 *  
 * */
public class CustomerDataMgt extends DataMgt<Customer> {
	private Vector<Customer> collect;

	public CustomerDataMgt() { // ������
		collect = getCollect();
	}

	@Override
	public Customer selectByName(String name) {
		int slength = name.length();

		if (slength == 1) { // ������ �Էµ� ���
			String lastname;
			for (Customer obj : collect) { // Vector�� ����� �� �� �̸��� ��ġ�ϴ� �� �ִٸ� ��������. ������ null ����.
				lastname = obj.getName().substring(0,1);
				if (name.equals(lastname)) {
					return obj;
				}
			}
			return null;
		}

		else if (slength == 2) { // �̸��� �Էµ� ���
			String firstname;
			for (Customer obj : collect) { // Vector�� ����� �� �� �̸��� ��ġ�ϴ� �� �ִٸ� ��������. ������ null ����.
				firstname = obj.getName().substring(1, 3);
				if (name.equals(firstname)) {
					return obj;
				}
			}
			return null;
		}

		else {
			String fullname;
			for (Customer obj : collect) { // Vector�� ����� �� �� �̸��� ��ġ�ϴ� �� �ִٸ� ��������. ������ null ����.
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
		for (Customer obj : collect) { // Vector�� ����� �� �� id�� ��ġ�ϴ� ���� �ִٸ� ��������. ������ null ����.
			if (id.equals(obj.getLoginId())) {
				return obj;
			}
		}

		return null;
	}

}
