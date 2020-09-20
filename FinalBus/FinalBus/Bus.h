#include <conio.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
using namespace std;

const int priceGoods = 10000;
static int P = 0;
static int Q = 1;


void ResizeConsole(int width, int height);
void FixConsoleWindow();

void GotoXY(int x, int y);


class Date
{
protected:
    int _day, _month, _year;

public:
    Date();
    void input();
    void output();
};

class Person {
protected:
    string _name, _sex;
    string _yearOfBirth;
    string _telephone;
    string _email;

public:
    Person();
    void input();
    void output();
};

class Ticket {
private:
    Date _date;
    string _nameOfTrip;
    vector<string> seatNumbers;

public:
    // Defalt Constructor
    Ticket();

    // Set Attributes
    void setSeatNumbers(vector<string> seatNumber);
    void setNameOfTrip(string nameOfTrip);
    void setDate(Date date);

    // Get Attributes

};

class User : public Person {
protected:
    string username;
    string password;
    int _goods;
    int _totalOfMoney;
    string _feedback;
    string _typeOfBus;
    Ticket _ticket;

public:
    // Default Constructor
    User();

    // Method
    void input();
    void output();

    // Get Attributes
    string getNameUser();
    
    // Set Attributes
    void setWeightOfGoods(int weight);
    void setTypeOfBus(string typeOfBus);
    void setTotalOfMoney(int totalOfMoney);
    void addFeedBack(string feedback);
    void setForTicket();
};

class Bus
{
protected:
    string _name = "Regular Bus";
    int Price;
    string Departure;
    string From;
    string To;
    int seat_max;
    int Row, Col;
    vector<vector<string>>Seats;
    string Driver;
    string Voucher;
public:
    int Number;
    void SetSeats();
    void Install();
    void Reserve(User &user);
    void Show();
    virtual void ShowName()
    {
        cout << "Type bus: " << _name << endl;
    }
    virtual void ShowPrice()
    {
        cout << "Price per ticket: 200,000 VND" << endl;
    }
    void ShowSeat();
    bool CheckEmpty(int No);
    void NameRev(string name, int Seat);
    string getTypeOfBus();
    Bus();
};

//Class cac loai xe dac biet 
class Bed_Car :public Bus
{
private:
    string _name = "Bed Car";
    string Voucher;

public:
    void ShowName()
    {
        cout << "Type bus: " << _name << endl;
    }
    void ShowPrice()
    {
        cout << "Price per ticket: 400,000 VND" << endl;
    }

    Bed_Car(int num);

};

class VIP : public Bus
{
private:
    string _name = "Vip Car";
    string Voucher;
public:
    void ShowName()
    {
        cout << "Type bus: " << _name << endl;
    }
    void ShowPrice()
    {
        cout << "Price per ticket: 3,000,000 VND" << endl;
    }
    VIP(int num);
};

class SuperVip : public Bus//Xe rieng tai xe rieng
{
private:
    string _name = "SuperVip Car";
    string Voucher = "supervipVoucher";
public:
    void ShowName()
    {
        cout << "Type bus: " << _name << endl;
    }
    void ShowPrice()
    {
        cout << "Price per ticket: 10,000,000 VND" << endl;
    }
    SuperVip(int num);
};


class Admin {
private:
    string _username;
    string _password;

public:
    void setUsername(string str);
    void setPassword(string str);
    string getUsername();
    string getPassword();
};

class BusStation {
private:
    // Admin
    vector<Admin> _ad;
    int serial; // Serial Admin -> Xem Admin nào phụ trách những xe nào, những hành khách nào
    void setAdmin(); // Khởi tạo Account của 4 Admin
    void printOutAccount(); //  (TEST) In thông tin Admin account ra để kiểm tra
    
    // Bus
    vector<Bus*> _bus;
    
    // User
    vector<User> _user;
    
    // Ticket
    vector<Ticket> _ticket;

public:
    // Default Constructor
    BusStation();

    // Admin
    bool logInForAdmin();
    
    // User
    void TestUser_Input();
    void addUser();

    // Bus
    void addBed_car(Bed_Car a);
    void addVip(VIP b);
    void addVipCar(SuperVip c);
    void AddCar();
    void Rev();
    
    // Menu
	void CustomerMenu();
};
