package dvdhw;

/*
 * 1917017 박현아
 * 
 * 사람의 이름과 생년, 나이 정보를 저장.
 * 필드값에는 getter을 사용해 접근하도록 함
 * toString으로 이름과 나이 출력
 * 
 * */
import java.time.LocalDate;

public class Person {
	private String name;
	private int birthyear;
	private int age;

	public Person(String name, int birthyear) { // name, birthyear을 파라미터로 받고 birthyear활용해 age값까지 저장하는 생성자
		this.name = name;
		this.birthyear = birthyear;

		LocalDate today = LocalDate.now();
		age = today.getYear() - birthyear;
	}

	public Person(String name) { // name을 파라미터로 받고 birthyear와 age는 0으로 초기화하는 생성자
		this.name = name;
		this.birthyear = 0;
		age = 0;
	}

	public String getName() {
		return name;
	}

	public int getBirthyear() {
		return birthyear;
	}

	public int getAge() {
		return age;
	}

	@Override
	public String toString() {
		return "이름:" + name + " 나이:" + age + " ";
	}

}
