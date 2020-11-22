package dvdhw;

import java.util.Vector;

/*
 * 1917017 박현아
 * 
 * DataMgt를 상속받는 클래스. 제너릭 타입을 Dvd로 지정하고 추상메소드 2개 override함.
 * 
 * */
public class DvdDataMgt extends DataMgt<Dvd> {
	private Vector<Dvd> collect;

	public DvdDataMgt() {
		collect = getCollect();
	}

	@Override
	public Dvd selectByName(String name) {

		for (Dvd obj : collect) { // 제목이 일치하는 dvd가 있다면 반환. 없다면 null 반환.
			if (name.equals(obj.getTitle())) {
				return obj;
			}
		}

		return null;
	}

	@Override
	public Dvd selectById(String id) {
		for (Dvd obj : collect) { // ISBN이 일치하는 dvd가 있다면 반환. 없다면 null 반환.
			if (id.equals(obj.getISBN())) {
				return obj;
			}
		}

		return null;
	}

}
