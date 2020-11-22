package dvdhw;

/*
 * 1917017 ������
 * 
 * ����� �̸��� ����, ���� ������ ����.
 * �ʵ尪���� getter�� ����� �����ϵ��� ��
 * toString���� �̸��� ���� ���
 * 
 * */
import java.time.LocalDate;

public class Person {
	private String name;
	private int birthyear;
	private int age;

	public Person(String name, int birthyear) { // name, birthyear�� �Ķ���ͷ� �ް� birthyearȰ���� age������ �����ϴ� ������
		this.name = name;
		this.birthyear = birthyear;

		LocalDate today = LocalDate.now();
		age = today.getYear() - birthyear;
	}

	public Person(String name) { // name�� �Ķ���ͷ� �ް� birthyear�� age�� 0���� �ʱ�ȭ�ϴ� ������
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
		return "�̸�:" + name + " ����:" + age + " ";
	}

}
