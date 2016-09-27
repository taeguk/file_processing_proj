#include "datafile.h"

#define MODE GENERATION_OF_DATA_FILE

int main() 
{
#if MODE == GENERATION_OF_DATA_FILE
	/*
		프로젝트에 필요한 데이터 파일들을 만든다.
	*/

	tool::generate_data_files(tool::MIN_MEMBER_COUNT, 
		tool::MIN_STOCK_COUNT, tool::MIN_PURCHASE_COUNT);

#else
	/*
		정상적인 프로그램 시작.
	*/
	
#endif
}