package dvdhw;

enum Genre { // 장르를 표현하는 enum
	Action, Comic, Romantic, Drama, ETC
}

/*
 * 1917017 박현아
 * 
 * DVD의 ISBN, 제목, 제작자, 제조국, 장르에 대한 정보 저장하는 클래스. getter 사용해 필드 정보에 접근. toString
 * 사용해 모든 정보 출력
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
		return "ISBN:" + ISBN + " 제목:" + title + " 제작자:" + producer.getName() + " 제조국:" + manufactureContry + " 장르: "
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
