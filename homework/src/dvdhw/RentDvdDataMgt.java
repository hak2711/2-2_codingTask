package dvdhw;

import java.util.*;

/*
 * 1917017 ������
 * 
 * DataMgt ��ӹ޴� Ŭ����. ���ʸ� Ÿ���� RentDvd�� �����ϰ� �߻� �޼ҵ� 2�� override.
 * 
 * */
public class RentDvdDataMgt extends DataMgt<RentDvd> {
	private Vector<RentDvd> collect;

	public RentDvdDataMgt() {
		collect = getCollect();
	}

	@Override
	public RentDvd selectByName(String name) {
		for (RentDvd obj : collect) { // ������ ���� ���� �ִٸ� �ش� ������ �뿩 ���� ��ȯ. ���ٸ� null ��ȯ.
			Dvd dvd = obj.getDvd();
			if (name.equals(dvd.getTitle())) {
				return obj;
			}
		}

		return null;
	}

	@Override
	public RentDvd selectById(String id) {
		for (RentDvd obj : collect) { // ISBN�� ���� ���� �ִٸ� �ش� ������ �뿩 ���� ��ȯ. ���ٸ� null ��ȯ.
			Dvd dvd = obj.getDvd();
			if (id.equals(dvd.getISBN())) {
				return obj;
			}
		}

		return null;
	}

	public int removeReturnedDvd() { // �ݳ��� ���� ��� ����
		int num = 0;
		Iterator<RentDvd> iter = collect.iterator();

		while (iter.hasNext()) {
			RentDvd i = iter.next();
			if (i.isReturn()) { // �ݳ��� ������ ���
				iter.remove();
				num++;
			}
		}
		return num;
	}

}
