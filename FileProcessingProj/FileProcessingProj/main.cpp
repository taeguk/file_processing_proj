#include "datafile.h"

#define MODE GENERATION_OF_DATA_FILE

int main() 
{
#if MODE == GENERATION_OF_DATA_FILE
	/*
		������Ʈ�� �ʿ��� ������ ���ϵ��� �����.
	*/

	tool::generate_data_files(tool::MIN_MEMBER_COUNT, 
		tool::MIN_STOCK_COUNT, tool::MIN_PURCHASE_COUNT);

#else
	/*
		�������� ���α׷� ����.
	*/
	
#endif
}