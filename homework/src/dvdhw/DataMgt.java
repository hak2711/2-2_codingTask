package dvdhw;

import java.util.Vector;

/*
 * 1917017 박현아
 * 
 * Vector를 사용해 데이터를 관리하는 추상 클래스.
 * StringBuilder를 사용해 Vector에 담긴 모든 정보(toString값)을 반환.
 * 이름과 아이디로 제품 찾는 추상 메소드 존재.
 * 
 * */
public abstract class DataMgt<T> {

	private Vector<T> collect = new Vector<T>();

	public Vector<T> getCollect() {
		return collect;
	}

	public void add(T item) { // 대상 하나 추가
		collect.add(item);
	}

	public void delete(T item) { // 대상 하나 삭제
		collect.remove(item);
	}

	public String showAll() { // 전체 검색
		int i = 1;
		StringBuilder strBuilder = new StringBuilder();

		if (collect.isEmpty()) // 검색 결과가 없는 경우
			return null;

		for (T c : collect) {
			strBuilder.append("[" + (i++) + "] " + c.toString() + "\n");
		}

		return strBuilder.toString();
	}

	public T get(int i) { // i번째 대상 반환
		return collect.get(i);
	}

	public void removeAll() { // 전체 삭제
		collect.clear();
	}

	public abstract T selectByName(String name);

	public abstract T selectById(String id);

}
