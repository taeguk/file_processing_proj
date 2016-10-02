#include <string>
#include <iostream>


/*
	Data Model에 관련된 것들을 담고 있다.
*/
namespace model {


	/*
		각종 상수들
	*/
	const int MEMBER_FIELD_NUM = 6;
	const int STOCK_FIELD_NUM = 7;
	const int PURCHASE_FIELD_NUM = 4;

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
		Member();
		Member(const std::string& id, const std::string& name, 
			const std::string& phone_number, const std::string& address, 
			const std::string& birthday, const std::string& email);
		Member(const Member&);
		Member& operator=(const Member&);
		bool operator==(const Member&) const;
		bool operator!=(const Member&) const;

		inline std::string id() const;
		inline std::string name() const;
		inline std::string phone_number() const;
		inline std::string address() const;
		inline std::string birthday() const;
		inline std::string email() const;

		friend std::istream& operator>> (std::istream&, Member&);
		friend std::ostream& operator<< (std::ostream&, const Member&);

	private:
		std::string m_id;
		std::string m_name;
		std::string m_phone_number;
		std::string m_address;
		std::string m_birthday;
		std::string m_email;
	};

	std::istream& operator>> (std::istream&, Member&);
	std::ostream& operator<< (std::ostream&, const Member&);

	std::string Member::id() const { return m_id; }
	std::string Member::name() const { return m_name; }
	std::string Member::phone_number() const { return m_phone_number; }
	std::string Member::address() const { return m_address; }
	std::string Member::birthday() const { return m_birthday; }
	std::string Member::email() const { return m_email; }


	/*
		재고 상품에 대한 정보를 나타내는 나타내는 Stock
	*/
	class Stock {
	public:
		Stock();
		Stock(const std::string& id, const std::string& category, 
			const std::string& material, int price,
			int stock, const std::string& washing_info,
			const std::string& size);
		Stock(const Stock&);
		Stock& operator=(const Stock&);
		bool operator==(const Stock&) const;
		bool operator!=(const Stock&) const;

		inline std::string id() const;
		inline std::string category() const;
		inline std::string material() const;
		inline int price() const;
		std::string formatted_price() const;
		inline int stock() const;
		inline std::string washing_info() const;
		inline std::string size() const;

		friend std::istream& operator>> (std::istream&, Stock&);
		friend std::ostream& operator<< (std::ostream&, const Stock&);

	private:
		std::string m_id;
		std::string m_category;
		std::string m_material;
		int m_price;
		int m_stock;
		std::string m_washing_info;
		std::string m_size;
	};

	std::istream& operator>> (std::istream&, Stock&);
	std::ostream& operator<< (std::ostream&, const Stock&);
	
	std::string Stock::id() const { return m_id; }
	std::string Stock::category() const { return m_category; }
	std::string Stock::material() const { return m_material; }
	int Stock::price() const { return m_price; }
	int Stock::stock() const { return m_stock; }
	std::string Stock::washing_info() const { return m_washing_info; }
	std::string Stock::size() const { return m_size; }


	/*
		상품 구매 내역에 대한 정보를 나타내는 Purchase
	*/
	class Purchase {
	public:
		Purchase();
		Purchase(const std::string& id, const std::string& stock_id,
			const std::string& member_id, int quantity);
		Purchase(const Purchase&);
		Purchase& operator=(const Purchase&);
		bool operator==(const Purchase&) const;
		bool operator!=(const Purchase&) const;

		inline std::string id() const;
		inline std::string stock_id() const;
		inline std::string member_id() const;
		inline int quantity() const;

		friend std::istream& operator>> (std::istream&, Purchase&);
		friend std::ostream& operator<< (std::ostream&, const Purchase&);

	private:
		std::string m_id;
		std::string m_stock_id;
		std::string m_member_id;
		int m_quantity;
	};

	std::istream& operator>> (std::istream&, Purchase&);
	std::ostream& operator<< (std::ostream&, const Purchase&);

	std::string Purchase::id() const { return m_id; }
	std::string Purchase::stock_id() const { return m_stock_id; }
	std::string Purchase::member_id() const { return m_member_id; }
	int Purchase::quantity() const { return m_quantity; }

}