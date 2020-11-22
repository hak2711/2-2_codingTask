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

		for (Customer obj : collect) { // Vector�� ����� �� �� �̸��� ��ġ�ϴ� �� �ִٸ� ��������. ������ null ����.
			if (name.equals(obj.getName())) {
				return obj;
			}
		}

		return null;
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
