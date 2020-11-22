package dvdhw;

import java.util.Scanner;

/*
 * 1917017 박현아
 * 
 * Dvd를 고객에게 대여해주는 DvdShop 클래스.
 * 고객 정보 관리자와 디비디 정보 관리자, 대여목록 관리자, 매니저 정보 등을 필드에 포함.
 * 로그인시도, 프로그램 실행, 메뉴 출력, 메뉴에 해당하는 기능 구현한 메소드를 포함.
 * 
 * 
 * */
public class DvdShop {
	private static Scanner sc = new Scanner(System.in);

	private CustomerDataMgt customers = new CustomerDataMgt(); // 고객정보 관리
	private DvdDataMgt dvds = new DvdDataMgt(); // 디비디 정보 관리
	private RentDvdDataMgt rentDvds = new RentDvdDataMgt(); // 디비디 대여 정보 관리
	private ManagerData manager = new ManagerData();

	public static void main(String[] args) {
		DvdShop dvdShop = new DvdShop();
		int i = 0;
		while (true) {
			if (dvdShop.loginTry()) { // 로그인 시도 성공한 경우
				dvdShop.start(); // 프로그램 실행
				break;
			} else { // 로그인 시도 실패한 경우
				if (i >= 2) { // 로그인 시도 실패 횟수가 3번을 넘어가면 프로그램 강제 종료
					System.out.println("프로그램 종료.");
					break;
				} else {
					System.out.println("아이디가 없거나 아이디 혹은 비밀번호가 일치하지 않습니다. 남은 시도 횟수 : " + (2 - i));
					i++;
				}
			}
		}
	}

	public boolean loginTry() { // 로그인 시도 메소드
		System.out.print("아이디와 비밀번호를 입력하시오 : ");
		String id = sc.next();
		String pw = sc.next();

		return manager.isManager(id, pw);
	}

	public void start() { // dvdshop 프로그램 실행
		decoConsole(true, "=");
		System.out.println("Hyunah DVD Shop"); // <== 본인의 이름으로 변경할 것 (예: 나이화 DVD Shop)
		decoConsole(false, "=");

		while (true) {
			System.out.println();

			int menu = showMenu(); // 메뉴 출력 후 사용자의 메뉴 선택을 입력받아 반환함
			if (menu == 0)
				break; // 0이 입력되면 종료

			switch (menu) {
			case 1:
				newCustomer();
				break; // 신규가입
			case 2:
				searchCustomer();
				break; // 고객검색
			case 3:
				customersShowAll();
				break; // 전체고객검색
			case 4:
				deleteCustomer();
				break; // 고객 삭제
			case 5:
				newDvd();
				break; // DVD 등록
			case 6:
				searchDvd();
				break; // DVD 검색
			case 7:
				dvdsShowAll();
				break; // DVD 전체 검색
			case 8:
				deleteDvd();
				break; // DVD 삭제
			case 9:
				rentDvd();
				break; // DVD 대여
			case 10:
				returnDvd();
				break; // DVD 반납
			case 11:
				rentDvdsShowAll();
				break; // 대여중 DVD 전체 검색
			case 12:
				deleteReturnedDvds();
				break; // 반납 완료된 DVD 삭제
			}
		}

	}

	public static int showMenu() { // 메뉴 출력하고 사용자에게 메뉴 입력받음.
		int menu = -1;

		while (true) { // 메뉴 출력
			System.out.println("============================= 메뉴 =============================");
			System.out.println("(0) 종료 (1) 신규가입 (2) 고객검색 (3) 전체고객검색 (4) 고객삭제");
			System.out.println("_______________________________________________________________");
			System.out.println("(5) DVD 등록 (6) DVD 검색 (7) DVD 전체검색  (8) Dvd 삭제");
			System.out.println("_______________________________________________________________");
			System.out.println("(9) DVD 대여 (10) DVD 반납 (11) 대여 목록 전체검색 (12) 대여 목록 전체 삭제");
			System.out.println("_______________________________________________________________");

			System.out.print("메뉴를 선택하세요 >> ");

			try {
				menu = Integer.parseInt(sc.next());
				if (0 > menu || menu > 12) // 메뉴 번호 범위 벗어난 경우
					throw new OutofRangeException();
				else
					break;
			} catch (NumberFormatException e) { // 사용자의 입력이 숫자가 아닌 경우
				System.out.println("숫자를 입력하십시오.");
			} catch (OutofRangeException e) { // 사용자의 입력이 메뉴 범위에 해당하지 않는 경우
				System.out.println(e.getMessage());
			}

		}

		System.out.println();
		return menu;
	}

	public static void decoConsole(boolean pre, String deco) { // 프로그램 꾸미는 메소드
		if (pre)
			System.out.println();

		for (int i = 0; i < 30; i++)
			System.out.print(deco);

		System.out.println();
		if (!pre)
			System.out.println();
	}

	private void customersShowAll() { // 전체 고객 검색
		String str = customers.showAll();

		if (str == null) // 검색 결과가 없는 경우
			System.out.println("고객 검색 결과가 없습니다.");
		else
			System.out.println(str);
	}

	private void dvdsShowAll() { // 전체 디비디 검색
		String str = dvds.showAll();

		if (str == null) // 검색 결과가 없는 경우
			System.out.println("Dvd 검색 결과가 없습니다.");
		else
			System.out.println(str);
	}

	private void rentDvdsShowAll() { // 전체 대여 목록 검색
		String str = rentDvds.showAll();

		if (str == null) // 검색 결과가 없는 경우
			System.out.println("대여 목록 검색 결과가 없습니다.");
		else
			System.out.println(str);
	}

	private void searchCustomer() { // 특정 고객 검색
		System.out.print("검색할 고객 이름을 입력세요 >> ");

		String name = sc.next();
		Customer cust = customers.selectByName(name);

		if (cust == null) // 검색 결과가 없는 경우
			System.out.println("고객 정보가 없습니다.");
		else
			System.out.println("\n결과>> " + cust.toString());

	}

	private void searchDvd() { // 특정 디비디 검색
		System.out.print("검색할 Dvd 제목을 입력세요 >> ");

		String title = sc.next();
		Dvd dvd = dvds.selectByName(title);

		if (dvd == null) // 검색 결과가 없는 경우
			System.out.println("Dvd 정보가 없습니다.");
		else
			System.out.println("\n결과>> " + dvd.toString());

	}

	private void deleteCustomer() { // 특정 고객 삭제
		int num = 0;

		System.out.print("삭제할 고객 이름을 입력세요 >> ");

		String name = sc.next();
		Customer cust = customers.selectByName(name);

		while (cust != null) { // 해당 이름을 가진 고객 정보를 모두 삭제하고 삭제된 고객 개수를 카운트.
			customers.delete(cust);
			cust = customers.selectByName(name);
			num++;
		}

		System.out.println(num + "개의 고객이 삭제되었습니다.");

	}

	private void deleteDvd() { // 특정 디비디 삭제
		int num = 0;

		System.out.print("삭제할 Dvd 제목을 입력세요 >> ");

		String name = sc.next();
		Dvd dvd = dvds.selectByName(name);

		while (dvd != null) { // 해당 제목을 가진 디비디 정보를 모두 삭제하고 삭제된 디비디 개수를 카운트.
			dvds.delete(dvd);
			RentDvd rentdvd = rentDvds.selectByName(name);

			if (rentdvd != null) { // 해당 제목을 가진 디비디가 대여 목록에 존재하면 그 정보도 삭제.
				rentDvds.delete(rentdvd);
			}
			dvd = dvds.selectByName(name);
			num++;
		}

		System.out.println(num + "개의 Dvd가 삭제되었습니다.");

	}

	private void deleteReturnedDvds() { // 반납 완료된 디비디 목록 삭제
		System.out.println(rentDvds.removeReturnedDvd() + "개의 반납 완료된 Dvd가 삭제되었습니다.");
	}

	public void newCustomer() { // 신규 고객 추가
		String name, id, addr, phone;
		int year;

		while (true) {
			System.out.println("고객 정보를 입력하세요(이름, 생년, 아이디, 주소, 전화번호 순으로 입력) >>");

			name = sc.next();
			year = sc.nextInt();
			id = sc.next();
			addr = sc.next();
			phone = sc.next();

			if (customers.selectById(id) != null) // 아이디가 중복된 경우
				System.out.println("이미 존재하는 아이디입니다. 다시 입력하세요.");

			else // 아이디가 중복되지 않은 경우
				break;
		}

		Customer cust = new Customer(name, year, id, addr, phone);
		customers.add(cust);
		System.out.println("신규 고객을 등록했습니다.");
	}

	public void newDvd() { // 새로운 디비디 등록
		String isbn, title, producer, contry;
		while (true) {
			System.out.println("Dvd 정보를 입력하세요(ISBN, 제목, 제작자, 제조국, 장르(1.액션,2.코믹,3.로맨틱,4.드라마,5.기타) >>");

			sc.nextLine();
			isbn = sc.next();
			title = sc.next();
			producer = sc.next();
			contry = sc.next();

			if (dvds.selectById(isbn) != null)// ISBN이 중복되는 경우
				System.out.println("이미 존재하는 ISBN입니다. 다시 입력하세요.");
			else // ISBN이 중복되지 않는 경우
				break;
		}

		Genre genre = Genre.ETC;
		int num = Integer.parseInt(sc.next()); // 장르 선택
		if (num == 1)
			genre = Genre.Action;
		else if (num == 2)
			genre = Genre.Comic;
		else if (num == 3)
			genre = Genre.Romantic;
		else if (num == 4)
			genre = Genre.Drama;
		else
			genre = Genre.ETC;

		Dvd dvd = new Dvd(isbn, title, new Person(producer), contry, genre);
		System.out.println("DVD를 등록했습니다.");
		dvds.add(dvd);
	}

	public void rentDvd() { // 디비디 대여
		System.out.print("대여를 원하는 고객 아이디와 대여할 Dvd의 ISBN을 입력하세요 >> ");

		String id = sc.next();
		String isbn = sc.next();

		if ((rentDvds.selectById(isbn) != null) && (!rentDvds.selectById(isbn).isReturn())) // 대여 목록에 있고 반납된 상태가 아닌 경우
			System.out.println("다른 고객이 대여 중인 Dvd입니다.");

		else if (dvds.selectById(isbn) == null) // 해당 isbn을 가진 dvd를 찾을 수 없는 경우
			System.out.println("Dvd를 찾을 수 없습니다.");

		else if (customers.selectById(id) == null) // 해당 id를 가진 고객을 찾을 수 없는 경우
			System.out.println("고객을 찾을 수 없습니다.");

		else { // 다른 고객이 대여 중이 아닌 경우
			Customer cust = customers.selectById(id);
			Dvd dvd = dvds.selectById(isbn);

			RentDvd rentInfo = new RentDvd(cust, dvd);
			rentDvds.add(rentInfo);
			System.out.println("대여가 완료되었습니다.");
		}
	}

	public void returnDvd() { // 디비디 반납
		System.out.print("반납할 Dvd의 ISBN을 입력하세요 >> ");

		String isbn = sc.next();

		RentDvd rentDvd = rentDvds.selectById(isbn);

		if (rentDvd == null) // 대여한 적 없는 디비디인 경우
			System.out.println("해당 Dvd는 대여 목록에 존재하지 않습니다.");

		else { // 대여한 디비디인 경우
			rentDvd.setReturn();
			System.out.println("반납이 완료되었습니다.");
		}
	}
}
