package dvdhw;

enum Genre { // �帣�� ǥ���ϴ� enum
	Action, Comic, Romantic, Drama, ETC
}

/*
 * 1917017 ������
 * 
 * DVD�� ISBN, ����, ������, ������, �帣�� ���� ���� �����ϴ� Ŭ����. getter ����� �ʵ� ������ ����. toString
 * ����� ��� ���� ���
 * 
 */
public class Dvd {
	private String ISBN;
	private String title;
	private Person producer;
	private String manufactureContry;
	private Genre genre;

	public Dvd(String ISBN, String title, Person producer, String manufactureContry, Genre genre) {
		this.ISBN = ISBN;
		this.title = title;
		this.producer = producer;
		this.manufactureContry = manufactureContry;
		this.genre = genre;
	}

	@Override
	public String toString() {
		return "ISBN:" + ISBN + " ����:" + title + " ������:" + producer.getName() + " ������:" + manufactureContry + " �帣: "
				+ genre;
	}

	public String getISBN() {
		return ISBN;
	}

	public String getTitle() {
		return title;
	}

	public Person getProducer() {
		return producer;
	}

	public String getManufactureContry() {
		return manufactureContry;
	}

	public Genre getGenre() {
		return genre;
	}

}
