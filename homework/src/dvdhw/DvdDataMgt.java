package dvdhw;

import java.util.Vector;

/*
 * 1917017 ������
 * 
 * DataMgt�� ��ӹ޴� Ŭ����. ���ʸ� Ÿ���� Dvd�� �����ϰ� �߻�޼ҵ� 2�� override��.
 * 
 * */
public class DvdDataMgt extends DataMgt<Dvd> {
	private Vector<Dvd> collect;

	public DvdDataMgt() {
		collect = getCollect();
	}

	@Override
	public Dvd selectByName(String name) {

		for (Dvd obj : collect) { // ������ ��ġ�ϴ� dvd�� �ִٸ� ��ȯ. ���ٸ� null ��ȯ.
			if (name.equals(obj.getTitle())) {
				return obj;
			}
		}

		return null;
	}

	@Override
	public Dvd selectById(String id) {
		for (Dvd obj : collect) { // ISBN�� ��ġ�ϴ� dvd�� �ִٸ� ��ȯ. ���ٸ� null ��ȯ.
			if (id.equals(obj.getISBN())) {
				return obj;
			}
		}

		return null;
	}

}
