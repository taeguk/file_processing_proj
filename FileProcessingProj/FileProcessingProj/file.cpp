#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <file.h>
#include <model/model.h>
#include <helpers.h>

using namespace std;
using namespace model;


namespace file 
{


	/*
		각종 Data Model들을 자동으로 생성해주는 함수
	*/
	static vector<Member> generate_random_member_list(int member_count);
	static vector<Stock> generate_random_stock_list(int stock_count);
	static vector<Purchase> generate_random_purchase_list(int purchase_count, 
		const vector<Member>& members, const vector<Stock>& stocks);


	void generate_list_files(int member_count, int stock_count, int purchase_count)
	{
		srand(static_cast<unsigned int>(time(NULL)));

		vector<Member> members = generate_random_member_list(member_count);
		vector<Stock> stocks = generate_random_stock_list(stock_count);
		vector<Purchase> purchases = generate_random_purchase_list(purchase_count,
			members, stocks);


		ofstream ofs_member, ofs_stock, ofs_purchase;

		ofs_member.open(MEMBER_LIST_FILE_NAME);
		ofs_stock.open(STOCK_LIST_FILE_NAME);
		ofs_purchase.open(PURCHASE_LIST_FILE_NAME);

		ofs_member << member_count << endl;
		for (int i = 0; i < member_count; ++i) 
		{
			const Member& member = members[i];
			ofs_member << member.id() << '|' << member.name() << '|'
				<< member.phone_number() << '|' << member.address() << '|'
				<< member.birthday() << '|' << member.email() << endl;
		}

		ofs_stock << stock_count << endl;
		for (int i = 0; i < stock_count; ++i) 
		{
			const Stock& stock = stocks[i];
			ofs_stock << stock.id() << '|' << stock.category() << '|'
				<< stock.material() << '|' << stock.formatted_price() << '|'
				<< stock.stock() << '|' << stock.washing_info() << '|'
				<< stock.size() << endl;
		}

		ofs_purchase << purchase_count << endl;
		for (int i = 0; i < purchase_count; ++i) 
		{
			const Purchase& purchase = purchases[i];
			ofs_purchase << purchase.id() << '|' << purchase.stock_id() << '|'
				<< purchase.member_id() << '|' << purchase.quantity() << endl;
		}
	}

	static vector<Member> generate_random_member_list(int member_count)
	{
		assert(member_count > 0);

		vector<Member> members;
		vector<string> avail_names;
		vector<string> avail_addresses;

		int avail_name_cnt = static_cast<int>(max(member_count * 0.8, 1.0));
		int avail_address_cnt = static_cast<int>(max(member_count * 0.3, 1.0));

		for (int i = 0; i < avail_name_cnt; ++i) 
		{
			avail_names.push_back("name_" + helper::to_string(i));
		}
		for (int i = 0; i < avail_address_cnt; ++i) 
		{
			avail_addresses.push_back("address_" + helper::to_string(i));
		}

		for (int i = 0; i < member_count; ++i) 
		{
			string id, name, phone_number, address, birthday, email;

			// Generate id
			id = "member_id_" + helper::to_string(i);

			// Generate name
			name = avail_names[rand() % avail_names.size()];

			// Generate phone_number
			{
				const vector<string> first_parts = { "010", "017", "014", "011" };

				string first_part = first_parts[rand() % first_parts.size()];
				string second_part = helper::to_string(rand() % 10000, 4);
				string third_part = helper::to_string(rand() % 10000, 4);

				phone_number = first_part + second_part + third_part;
			}

			// Generate address
			address = avail_addresses[rand() % avail_addresses.size()];

			// Generate birthday
			{
				int min_year = 1910, max_year = 2015;
				int min_month = 1, max_month = 12;
				int min_day = 1, max_day = 28;

				string year = helper::to_string(min_year + rand() % (max_year - min_year + 1), 4);
				string month = helper::to_string(min_month + rand() % (max_month - min_month + 1), 2);
				string day = helper::to_string(min_day + rand() % (max_day - min_day + 1), 2);

				birthday = year + month + day;
			}

			// Generate email
			{
				const vector<string> email_hosts = { 
					"sogang.ac.kr", "naver.com", "google.com", "hanmail.net" 
				};
				const string& email_host = email_hosts[rand() % email_hosts.size()];
				email = "username_" + helper::to_string(i) + "@" + email_host;
			}

			members.push_back(Member(id, name, phone_number, address, birthday, email));
		}

		return members;
	}

	static vector<Stock> generate_random_stock_list(int stock_count)
	{
		assert(stock_count > 0);

		vector<Stock> stocks;

		for (int i = 0; i < stock_count; ++i) 
		{
			string id, category, material, washing_info, size;
			int price, stock_;

			// Generate id
			id = "00" + helper::to_string(i, 8) + "00";

			// Generate category
			{
				// len <= 8
				const vector<string> categories = {
					"Shirts", "Pants", "Skirts", "Hoods", "Backpack",
					"Hat", "Socks"
				};

				category = categories[rand() % categories.size()];
			}

			// Generate material
			{
				const vector<string> materials = {
					"Denim", "Gold", "Silver", "Ruby", "Diamond"
				};

				material = materials[rand() % materials.size()];
			}

			// Generate price
			price = rand() % 100000;

			// Generate stock
			stock_ = rand() % 10000;

			// Generate washing_info
			{
				const vector<string> washing_infos = {
					"Dry Cleaning", "Hand Washing"
				};

				washing_info = washing_infos[rand() % washing_infos.size()];
			}

			// Generate size
			{
				const vector<string> sizes = {
					"S", "M", "L", "XL"
				};

				size = sizes[rand() % sizes.size()];
			}

			stocks.push_back(Stock(id, category, material, price, stock_, washing_info, size));
		}

		return stocks;
	}

	static vector<Purchase> generate_random_purchase_list(int purchase_count,
		const vector<Member>& members, const vector<Stock>& stocks)
	{
		assert(purchase_count > 0);

		vector<Purchase> purchases;

		for (int i = 0; i < purchase_count; ++i) 
		{
			string id, stock_id, member_id;
			int quantity;

			// Generate id
			id = "00" + helper::to_string(i, 12) + "00";

			// Generate stock_id
			stock_id = stocks[rand() % stocks.size()].id();

			// Generate member_id
			member_id = members[rand() % members.size()].id();

			// Generate quantity
			quantity = rand() % 100;

			purchases.push_back(Purchase(id, stock_id, member_id, quantity));
		}

		return purchases;
	}

}