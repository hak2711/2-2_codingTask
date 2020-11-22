package dvdhw;

import java.util.Vector;

/*
 * 1917017 ������
 * 
 * Vector�� ����� �����͸� �����ϴ� �߻� Ŭ����.
 * StringBuilder�� ����� Vector�� ��� ��� ����(toString��)�� ��ȯ.
 * �̸��� ���̵�� ��ǰ ã�� �߻� �޼ҵ� ����.
 * 
 * */
public abstract class DataMgt<T> {

	private Vector<T> collect = new Vector<T>();

	public Vector<T> getCollect() {
		return collect;
	}

	public void add(T item) { // ��� �ϳ� �߰�
		collect.add(item);
	}

	public void delete(T item) { // ��� �ϳ� ����
		collect.remove(item);
	}

	public String showAll() { // ��ü �˻�
		int i = 1;
		StringBuilder strBuilder = new StringBuilder();

		if (collect.isEmpty()) // �˻� ����� ���� ���
			return null;

		for (T c : collect) {
			strBuilder.append("[" + (i++) + "] " + c.toString() + "\n");
		}

		return strBuilder.toString();
	}

	public T get(int i) { // i��° ��� ��ȯ
		return collect.get(i);
	}

	public void removeAll() { // ��ü ����
		collect.clear();
	}

	public abstract T selectByName(String name);

	public abstract T selectById(String id);

}
