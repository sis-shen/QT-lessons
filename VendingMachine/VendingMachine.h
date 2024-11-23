#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <windows.h>
using namespace std;

struct Item
{
public:
	Item(const string& name,double price,int cnt)
		:_name(name),_price(price),_cnt(cnt)
	{}
public:
	string _name;
	double _price;
	int _cnt;
};

class VendingMachine
{
public:
	VendingMachine(int capacity = 100) :_amount(0), _sale(0),_capacity(capacity) {}

	void AutoInit()
	{
		if (_GoodsList.size() != 0)
		{
			cout << "不能重复初始化!!!" << endl;
			return;
		}
		_AddItem("小苹果", 5, 10);
		_AddItem("大香蕉", 2.5, 2);
		_AddItem("香蕉君", 30, 5);
		_AddItem("野兽先辈", 1145.14, 15);

	}
public:
	void Run()
	{

		int cmd = 1;
		do
		{
			PrintMenu();
			cout << "请输入操作码" << endl;
			cin >> cmd;
			switch (cmd)
			{
			case 0:
				break;
			case 1:
				AutoInit(); break;
			case 2:
				AddItem(); break;
			case 3:
				ShowItems(); SellItem(); break;
			case 4:
				Info(); break;
			case 5:
				ShowItems(); break;
			case 6:
				ShowItemsByName(); break;
			case 7:
				ShowItemsByName(true); break;
			case 8:
				ShowItemsByPrice(); break;
			case 9:
				ShowItemsByPrice(true); break;
			case 10:
				ShowItemsByCNT(); break;
			case 11:
				ShowItemsByCNT(true); break;
			case 12:
				InfoItem();
			default:
				cout << "未知操作码" << endl;
				break;
			}

			cout << "输入任意按键继续..." << endl;
			getchar();
			getchar();

		} while (cmd);
	}
private:
	void PrintMenu()
	{
		ClearScreen();
		printf("===========菜单=============\n");
		printf("0.退出 \n1.自动初始化 \n2.添加商品 \n3.购买商品 \n4.显示售货机信息  \n");

		cout << "5.默认顺序显示商品列表\n";
		cout << "6.按名称升序显示商品列表\n";
		cout << "7.按名称降序显示商品列表\n";
		cout << "8.按单价升序显示商品列表\n";
		cout << "9.按单价降序显示商品列表\n";
		cout << "10.按剩余量升序显示商品列表\n";
		cout << "11.按剩余量降序显示商品列表\n";
		cout << "12.按名称查询商品\n";


		printf("=============================\n\n");
	}

	void ClearScreen()
	{
		system("cls");
	}

public:
	bool SellItem()
	{
		string name;
		int num;
		cout << "请输入 [商品名] [数量]" << endl;
		cin >> name >> num;
		return _SellItem(name, num);
	}

    int _SellItem(const string& name,int num)
	{
		if (num <= 0)
		{
			cout << "非法的售卖数量: " << num << endl;
            return -1;
		}

		if (!_index.count(name))
		{
			cout << "不存在的商品: " << name << endl;
            return -1;
		}

		Item& item = _GoodsList[_index[name]];
		if (item._cnt < num)
		{
			cout << "交易失败，剩余库存不足！剩余: " << item._cnt << " 预期售卖: " << num << endl;
            return -1;
		}

		item._cnt -= num;
		double sum = num * item._price;
		_amount -= sum;
		_capacity += num;
		_sale += sum;
		printf("交易成功！商品名: %s,单价: %.2lf,交易数量: %d,本次交易额: %.2lf\n", name.c_str(), item._price, num, sum);
        return sum;
	}

    double SumValue(const string& name,int num)
    {
        if (num <= 0)
        {
            cout << "非法的售卖数量: " << num << endl;
            return -1;
        }

        if (!_index.count(name))
        {
            cout << "不存在的商品: " << name << endl;
            return -1;
        }

        Item& item = _GoodsList[_index[name]];
        if (item._cnt < num)
        {
            cout << "交易失败，剩余库存不足！剩余: " << item._cnt << " 预期售卖: " << num << endl;
            return -1;
        }


        double sum = num * item._price;

        return sum;
    }


    bool IsEnough(const string& name,int num)
    {
        return _GoodsList[_index[name]]._cnt >= num;
    }

public:
	void InfoItem()
	{
		string name;
		cout << "请输入待查询的商品名称" << endl;
		_InfoItem(name);
	}


    bool _InfoItem(const string& name)
	{
		if (!_index.count(name))
		{
			cout << "商品不存在" << endl;
            return false;
		}
		Item& item = _GoodsList[_index[name]];
		printf("商品名: %s,单价: %.2lf,剩余量: %d", name.c_str(), item._price, item._cnt);
        return true;
	}

public:
	bool AddItem()
	{
		Info();
		string name;
		double price;
		int num;
		cout << "请先后输入 [商品名称] [单价] [数量]" << endl;
		cin >> name >> price >> num;

		return _AddItem(name, price, num);
	}

    bool _AddItem(const Item&item)
    {
        return _AddItem(item._name,item._price,item._cnt);
    }


	bool _AddItem(const string& name, double price,int num)
	{
		if (_index.count(name))
		{
			//更新商品数量
			Item& item = _GoodsList[_index[name]];
			if (item._price != price)
			{
				cout << "商品添加失败，价格与记录不符: " << price << endl;
				return false;
			}
			item._cnt += num;
			_amount += price * num;
		}
		else
		{
			if (price <= 0)
			{
				cout << "非法单价: " << price << endl;
				return false;
			}
			if (num <= 0)
			{
				cout << "非法数量: " << num <<  endl;
				return false;
			}
			if (_capacity < num)
			{
				printf("容量不足， 容量: %d ，添加的数量: %d\n", _capacity, num);
				return false;
			}
			int sz = _GoodsList.size();
			_index[name] = sz;
			_GoodsList.push_back(Item(name, price, num));
			_amount += price * num;
			_capacity -= num;

			printf("商品添加成功，商品名: %s,单价: %.2lf,本次添加的数量: %d\n", name.c_str(), price, num);
			return true;
		}
        return true;
	}

    Item GetItem(const std::string& name)
    {
        return _GoodsList[_index[name]];
    }
public:
	void ShowItems()
	{
		cout << "默认顺序" << endl;
		_ShowItems(_GoodsList);
	}

	void ShowItemsByName(bool reverse_arr=false)//默认升序
	{
		if (reverse_arr)
		{
			cout << "按名字降序" << endl;
		}
		else cout << "按名字升序" << endl;
		auto copy = _GoodsList;
		sort(copy.begin(), copy.end(), [&](const Item& item1, const Item& item2) {
			if (item1._name <= item2._name)return true;
			else return false;
			});
		if (reverse_arr)
		{
			reverse(copy.begin(), copy.end());
		}
		_ShowItems(copy);
	}

	void ShowItemsByPrice(bool reverse_arr = false)//默认升序
	{
		if (reverse_arr)cout << "按单价降序" << endl;
		else cout << "按价格升序" << endl;
		auto copy = _GoodsList;
		sort(copy.begin(), copy.end(), [&](const Item& item1, const Item& item2) {
			if (item1._price <= item2._price)return true;
			else return false;
			});
		if (reverse_arr)
		{
			reverse(copy.begin(), copy.end());
		}
		_ShowItems(copy);
	}

	void ShowItemsByCNT(bool reverse_arr = false)//默认升序
	{
		if (reverse_arr) cout << "按剩余量降序" << endl;
		else cout << "按剩余量升序" << endl;
		auto copy = _GoodsList;
		sort(copy.begin(), copy.end(), [&](const Item& item1, const Item& item2) {
			if (item1._cnt <= item2._cnt)return true;
			else return false;
			});
		if (reverse_arr)
		{
			reverse(copy.begin(), copy.end());
		}
		_ShowItems(copy);
	}


	void _ShowItems(const vector<Item>& goodslist)
	{
		printf("%-10s %-10s %-4s\n", "商品名", "单价", "剩余数量");
		for (auto item : goodslist)
		{
			printf("%-10s %-10.2lf %-4d\n", item._name.c_str(), item._price, item._cnt);
		}
		printf("\n");
	}
public:

	void Info()
	{
		printf("商品数量: %u ,机器内商品总价值 %.2lf,总销售额: %.2lf,剩余容量: %d\n",
			_GoodsList.size(), _amount, _sale, _capacity);
	}

    double GetAmount(){return _amount;}
    double GetSale(){return _sale;}
    int Getcapacity(){return _capacity;}

private:
	vector<Item> _GoodsList; //储存商品列表
	unordered_map<string, int> _index; //储存名字指向索引的哈希表

	double _amount;//货物总价值
	double _sale;//总销售额
	int _capacity;//容量
};
