#include <string>


/*
	Data Model에 관련된 것들을 담고 있다.
*/
namespace model {


	/*
		각종 상수들
	*/
	const int MEMBER_BIRTHDAY_LEN = 8;
	const int STOCK_ID_LEN = 12;
	const int STOCK_CATEGORY_LEN = 8;
	const int STOCK_PRICE_LEN = 6;
	const int STOCK_STOCK_LEN = 4;
	const int STOCK_SIZE_LEN = 2;
	const int PURCHASE_ID_LEN = 16;
	const int PURCHASE_QUANTITY_LEN = 2;


	/*
		회원 정보를 나타내는 클래스 Member
	*/
	class Member {
	public:
		Member(const std::string& id, const std::string& name, 
			const std::string& phone_number, const std::string& address, 
			const std::string& birthday, const std::string& email);
		Member(const Member&);
		Member& operator=(const Member&);
		bool operator==(const Member&);
		bool operator!=(const Member&);

		inline std::string id();
		inline std::string name();
		inline std::string phone_number();
		inline std::string address();
		inline std::string birthday();
		inline std::string email();

	private:
		std::string m_id;
		std::string m_name;
		std::string m_phone_number;
		std::string m_address;
		std::string m_birthday;
		std::string m_email;
	};

	std::string Member::id() { return m_id; }
	std::string Member::name() { return m_name; }
	std::string Member::phone_number() { return m_phone_number; }
	std::string Member::address() { return m_address; }
	std::string Member::birthday() { return m_birthday; }
	std::string Member::email() { return m_email; }


	/*
		재고 상품에 대한 정보를 나타내는 나타내는 Stock
	*/
	class Stock {
	public:
		Stock(const std::string& id, const std::string& category, 
			const std::string& material, const std::string& price,
			const std::string& stock, const std::string& washing_info,
			const std::string& size);
		Stock(const Stock&);
		Stock& operator=(const Stock&);
		bool operator==(const Stock&);
		bool operator!=(const Stock&);

		inline std::string id();
		inline std::string category();
		inline std::string material();
		inline std::string price();
		inline std::string stock();
		inline std::string washing_info();
		inline std::string size();

	private:
		std::string m_id;
		std::string m_category;
		std::string m_material;
		std::string m_price;
		std::string m_stock;
		std::string m_washing_info;
		std::string m_size;
	};
	
	std::string Stock::id() { return m_id; }
	std::string Stock::category() { return m_category; }
	std::string Stock::material() { return m_material; }
	std::string Stock::price() { return m_price; }
	std::string Stock::stock() { return m_stock; }
	std::string Stock::washing_info() { return m_washing_info; }
	std::string Stock::size() { return m_size; }


	/*
		상품 구매 내역에 대한 정보를 나타내는 Purchase
	*/
	class Purchase {
	public:
		Purchase(const std::string& purchase_id, const std::string& stock_id,
			const std::string& member_id, const std::string& quantity);
		Purchase(const Purchase&);
		Purchase& operator=(const Purchase&);
		bool operator==(const Purchase&);
		bool operator!=(const Purchase&);

		inline std::string purchase_id();
		inline std::string stock_id();
		inline std::string member_id();
		inline std::string quantity();

	private:
		std::string m_purchase_id;
		std::string m_stock_id;
		std::string m_member_id;
		std::string m_quantity;
	};

	std::string Purchase::purchase_id() { return m_purchase_id; }
	std::string Purchase::stock_id() { return m_stock_id; }
	std::string Purchase::member_id() { return m_member_id; }
	std::string Purchase::quantity() { return m_quantity; }

}