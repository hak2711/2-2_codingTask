package dvdhw;

/*
 * 1917017 박현아
 * 
 * 메뉴 번호 범위에 벗어난 경우를 처리하는 예외 클래스
 * 
 * */

class OutofRangeException extends Exception {
	public String getMessage() {
		return "메뉴 번호 범위에 해당하지 않는 숫자입니다.";
	}
}
