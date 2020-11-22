package dvdhw;

import java.util.*;

/*
 * 1917017 박현아
 * 
 * DataMgt 상속받는 클래스. 제너릭 타입을 RentDvd로 지정하고 추상 메소드 2개 override.
 * 
 * */
public class RentDvdDataMgt extends DataMgt<RentDvd> {
	private Vector<RentDvd> collect;

	public RentDvdDataMgt() {
		collect = getCollect();
	}

	@Override
	public RentDvd selectByName(String name) {
		for (RentDvd obj : collect) { // 제목이 같은 디비디가 있다면 해당 디비디의 대여 정보 반환. 없다면 null 반환.
			Dvd dvd = obj.getDvd();
			if (name.equals(dvd.getTitle())) {
				return obj;
			}
		}

		return null;
	}

	@Override
	public RentDvd selectById(String id) {
		for (RentDvd obj : collect) { // ISBN이 같은 디비디가 있다면 해당 디비디의 대여 정보 반환. 없다면 null 반환.
			Dvd dvd = obj.getDvd();
			if (id.equals(dvd.getISBN())) {
				return obj;
			}
		}

		return null;
	}

	public int removeReturnedDvd() { // 반납된 디비디 목록 삭제
		int num = 0;
		Iterator<RentDvd> iter = collect.iterator();

		while (iter.hasNext()) {
			RentDvd i = iter.next();
			if (i.isReturn()) { // 반납된 디비디인 경우
				iter.remove();
				num++;
			}
		}
		return num;
	}

}
