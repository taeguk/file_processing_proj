#include <string>


/*
	 프로젝트에 필요한 도구들을 담고 있다.
	 프로젝트의 직접적인 실행에 사용되진 않고, 테스트라던지 도구용도로 쓰인다.
*/
namespace tool {


	/*
		프로젝트에서 요구하는 최소 데이터 개수
	*/
	const int MIN_MEMBER_COUNT = 1000;
	const int MIN_STOCK_COUNT = 1000;
	const int MIN_PURCHASE_COUNT = 10000;


	/*
	생성할 데이터 파일 이름을 저장하고 있는 상수들
	*/
	const std::string MEMBER_LIST_FILE_NAME = "listOfMember.txt";
	const std::string STOCK_LIST_FILE_NAME = "listOfStock.txt";
	const std::string PURCHASE_LIST_FILE_NAME = "listOfPurchase.txt";


	/*
		데이터 파일들을 임의로 생성해주는 함수
	*/
	void generate_data_files(int member_count, int stock_count, int purchase_count);
}