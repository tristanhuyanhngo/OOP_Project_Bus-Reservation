#include"Bus.h"

void FixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ResizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void vline(char ch = '-')
{
	for (int i = 80; i > 0; i--)
		cout << ch;
}

void Draw(string Option)
{
	for (int i = 0; i < 48; i++)
	{
		GotoXY(i, 1);
		cout << "\xCD";
	}
	for (int i = 62; i < 120; i++)
	{
		GotoXY(i, 1);
		cout << "\xCD";
	}
	GotoXY(50, 1);
	cout << Option << endl;
}

//BUS

Bus::Bus()
{
	Number = 0;
	Driver = " ";
	Departure = " ";
	From = " ";
	To = " ";
	Price = 200000;
	Col = 5;
	Row = 8;
	seat_max = Row * Col;
	SetSeats();
}

Bed_Car::Bed_Car(int num)
{
	Number = num;
	Driver = " ";
	Departure = " ";
	From = " ";
	To = " ";
	Price = 400000;
	Col = 3;
	Row = 6;
	seat_max = Row * Col;
	SetSeats();
}

VIP::VIP(int num)
{
	Number = num;
	Driver = " ";
	Departure = " ";
	From = " ";
	To = " ";
	Price = 3000000;
	Col = 2;
	Row = 5;
	seat_max = Row * Col;
	SetSeats();
}

SuperVip::SuperVip(int num)
{
	Number = num;
	Driver = " ";
	Departure = " ";
	From = " ";
	To = " ";
	Price = 10000000;
	Col = 2;
	Row = 1;
	seat_max = Row * Col;
	SetSeats();
}

void Bus::SetSeats()
{
	Seats.resize(Row);
	for (int i = 0; i < Row; i++)
		Seats[i].resize(Col);

	for (int i = 0; i < Row; i++)
		for (int j = 0; j < Col; j++)
		{
			Seats[i][j] = "Empty";
		}
}

void Bus::Install()// FOR ADMIN ONLY 
{

	cout << "Enter Bus No: ";
	cin >> Number;
	cin.ignore();

	cout << "\nEnter driver name: ";
	getline(cin, Driver);

	cout << "\nEnter Departure time: ";
	getline(cin, Departure);

	cout << "\nGoing From: ";
	getline(cin, From);

	cout << "\nTo: ";
	getline(cin, To);

	cout << "\nEnter Price: ";
	cin >> Price;
	cin.ignore();

	cout << "\nEnter Seat Rows and Cols: ";
	cin >> Row >> Col;
	cin.ignore();
	SetSeats();
	seatEmpty = seat_max = Row * Col;
	cout << "\nEnter Discount Voucher code: ";
	getline(cin, Voucher);


}

vector<string> split(string haystack, string separator = " ")
{
	vector<string> a;
	size_t Startpos = 0;
	while (true)
	{
		size_t Foundpos = haystack.find(separator, Startpos);
		if (Foundpos != string::npos)
		{
			string Token = haystack.substr(Startpos, Foundpos - Startpos);
			Startpos = Foundpos + separator.length();
			a.push_back(Token);
		}
		else
		{
			a.push_back(haystack.substr(Startpos, haystack.length() - Startpos));
			break;
		}

	}
	return a;
}

void Bus::ShowSeat()
{
	int No = 1;
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			cout << No << ". " << Seats[i][j] << "\t \t";
			No++;
		}
		cout << endl;
	}
}

void Bus::Show()// Show for Customer
{
	if (seatEmpty == 0) {
		return;
	}

	cout << "Bus No: " << Number << endl;
	ShowName();
	cout << "Driver: " << Driver << endl;
	cout << "Going From " << From << " To " << To << endl;
	cout << "Departure time: " << Departure << endl;
	cout << "Seat Available: " << seatEmpty << endl;
	ShowPrice();
}

bool Bus::CheckEmpty(int Seat)
{
	int Num = 1;
	for (int i = 0; i < Row; i++)
		for (int j = 0; j < Col; j++)
		{
			if (Num == Seat)
				if (strcmp(Seats[i][j].c_str(), "Empty") == 0)
					return true;
				else return false;
			Num++;
		}
	return false;
}

void Bus::NameRev(string Name, int Seat)
{
	int Num = 1;
	for (int i = 0; i < Row; i++)
		for (int j = 0; j < Col; j++)
		{
			if (Num == Seat)
				Seats[i][j] = Name;
			Num++;
		}
}

string Bus::getTypeOfBus()
{
	return _name;
}

string Bus::getNameOfTrip()
{
	return From + " To " + To;
}

void Bus::Reserve(User &user)// For Customer
{
	int Seat_no, num_of_people, Weight;
	int bill;
	string customer_Voucher, haystack;
	vector<string>s_seats;
	
	if (seatEmpty == 0) {
		cout << "Sorry! All of seats has already taken ! ";
		return;
	}

	cout << "What seat(s) you want to Reverse (You can pick multiple seat): ";
	getline(cin, haystack);

	s_seats = split(haystack);
	num_of_people = s_seats.size();

	for (int i = 0; i < num_of_people; i++)
	{
		Seat_no = stoi(s_seats[i]);
	top: 
		if (Seat_no > seat_max)
		{
			cout << "Seat " << Seat_no << " is out of max seats. Please try again. " << endl;
			cout << "Seat: ";
			cin >> Seat_no;
			cin.ignore();
			cout << endl;
			goto top;
		}

		if (CheckEmpty(Seat_no)) {
			NameRev(user.getNameUser(), Seat_no);
			seatEmpty--;
		}
		else
		{
			cout << "Seat " << Seat_no << " is already reverse. Please try again" << endl;
			cout << "Seat: ";
			cin >> Seat_no;
			cin.ignore();
			goto top;
		}

	}
	cout << "Enter Weight of your luggages: ";
	cin >> Weight;
	user.setWeightOfGoods(Weight);
	cin.ignore();

	bill = (Price * num_of_people) + (Weight * priceGoods);
	cout << "Enter Voucher(type no if you dont have): ";
	getline(cin, customer_Voucher);
	if (customer_Voucher == Voucher) {
		bill /= 2;
	}
	user.setTotalOfMoney(bill);
	user.setSeatNumbersForTicket(s_seats);
}



// Date
Date::Date()
{
	_day = _month = _year = 0;
}
void Date::input()
{
	cout << "Enter Day: ";
	cin >> _day;
	cout << "Enter month: ";
	cin >> _month;
	cout << "Enter year: ";
	cin >> _year;
}
void Date::output()
{
	cout << "Day/Month/Year: " << _day << "/" << _month << "/" << _year << endl;
}

//Person
Person::Person()
{
	_name = _sex = _email = _telephone = _yearOfBirth = "";
}

void Person::input()
{
	cin.ignore();

	cout << "\nEnter Your Full Name: ";
	getline(cin, _name);

	cout << "\nEnter Your Gender: ";
	getline(cin, _sex);

	cout << "\nEnter Your Year Of Birth: ";
	cin >> _yearOfBirth;
	cin.ignore();

	cout << "\nEnter Your Telephone: ";
	getline(cin, _telephone);

	cout << "\nEnter Your Email: ";
	getline(cin, _email);
}

void Person::output()
{
	cout << "Name: " << _name << endl;
	cout << "Telephone: " << _telephone << endl;
}

//User
User::User()
{
	_totalOfMoney = _goods = 0;
	username = password = _feedback = _typeOfBus = "";
}
 
void User::input()
{
	Person::input();
}

void User::output()
{
	Person::output();
	cout << "Type of Bus: " << _typeOfBus << endl;
	_ticket.output();
	cout << "Total Of Money: " << _totalOfMoney << endl;
}

string User::getNameUser()
{
	return _name;
}

void User::setWeightOfGoods(int weight)
{
	_goods = weight;
}

void User::setTypeOfBus(string typeOfBus)
{
	_typeOfBus = typeOfBus;
}

void User::setTotalOfMoney(int totalOfMoney)
{
	_totalOfMoney = totalOfMoney;
}

void User::addFeedBack(string feedback)
{
	_feedback = feedback;
}

void User::setSeatNumbersForTicket(vector<string> seatNumbers)
{
	_ticket.setSeatNumbers(seatNumbers);
}

void User::setNameOfTrip(string nameOfTrip)
{
	_ticket.setNameOfTrip(nameOfTrip);
}

// Tickets
Ticket::Ticket()
{
	_nameOfTrip = "";
	seatNumbers.clear();
}

void Ticket::setSeatNumbers(vector<string> seatNumber)
{
	seatNumbers = seatNumber;
}

void Ticket::setNameOfTrip(string nameOfTrip)
{
	_nameOfTrip = nameOfTrip;
}

void Ticket::setDate(Date date)
{
	_date = date;
}

void Ticket::output()
{
	cout << "Name of Trip: " << _nameOfTrip << endl;
	cout << "Seat Number(s): ";
	for (int i = 0; i < seatNumbers.size(); i++) {
		cout << seatNumbers[i] << " ";
	}
	cout << endl;
}

// BusStation
void BusStation::printOutAccount()
{
	for (int i = 0; i < _ad.size(); i++) {
		cout << _ad[i].getUsername() << _ad[i].getPassword() << "\n";
	}
}

void BusStation::TestUser_Input()
{
	User person;
	
	person.input();

	_user.push_back(person);

	_user[0].output();
}

void BusStation::setAdmin()
{
	Admin admin1;
	Admin admin2;
	Admin admin3;
	Admin admin4;

	admin1.setUsername("phunganhkhoa");
	admin1.setPassword("19127449");
	admin2.setUsername("ngodangkhoa");
	admin2.setPassword("19127444");
	admin3.setUsername("huynhcaonhathieu");
	admin3.setPassword("19127399");
	admin4.setUsername("ngohuyanh");
	admin4.setPassword("19127095");

	_ad.push_back(admin1);
	_ad.push_back(admin2);
	_ad.push_back(admin3);
	_ad.push_back(admin4);
}

BusStation::BusStation()
{
	_ad.clear();
	_bus.clear();
	_user.clear();
	_ticket.clear();
	serial = 0;
}

bool BusStation::logInForAdmin()
{
	bool validateAdmin = false;
	int numberOfWrongInput = 0;
	string username = "";
	string password = "";

	while (!validateAdmin) {
		Draw("Log In For Admin  ");
		cout << "Username: ";
		cin >> username;
		cin.ignore();
		cout << "Password: ";
		cin >> password;
		for (int i = 0; i < _ad.size(); i++) {
			if (_ad[i].getUsername() == username && _ad[i].getPassword() == password) {
				serial = i;
				return true;
			}
		}

		if (!validateAdmin) {
			cout << "Wrong Username or Password ! Please press Enter to try again ! " << "\n";
			numberOfWrongInput++;
			system("pause");
		}

		if (numberOfWrongInput == 3) {
			system("cls");
			cout << "You have entered wrong Username or Password 3 times ! Please press Enter to exit program ! " << "\n";
			return false;
		}

		username.clear();
		password.clear();
		system("cls");
	}

	return false;
}

void BusStation::addUser()
{
	User person;
	person.input();

	_user.push_back(person);
}

void BusStation::showTicketOfUser()
{
	_user[_user.size() - 1].output();
}

void BusStation::showPassenger()
{
	for (int i = 0; i < _user.size(); i++) {
		_user[i].output();
		cout << "\n";
	}
}

void BusStation::AddCar()
{
	
	int choice;
	while (true)
	{
		Draw("AdminSetup");
		GotoXY(40, 4);
		cout << "Enter type of Bus you want to Create " << endl;
		GotoXY(50, 6);
		cout << "1. Regular Bus " << endl;
		GotoXY(50, 8);
		cout << "2. Bed Car " << endl;
		GotoXY(50, 10);
		cout << "3. Vip " << endl;
		GotoXY(50, 12);
		cout << "4. Private Bus" << endl;
		GotoXY(50, 14);
		cout << "5. Exit" << endl;
		GotoXY(50, 16);
		cout << "Choice: ";
		cin >> choice;
		cin.ignore();
		
		if (choice == 5)
		{
			system("pause");
			system("cls");
			break;
		}
		system("cls");
		switch (choice)
		{
		case 1:
		{
			Draw("AdminSetup");
			int Num;
			cout << "Enter the number of bus you want to Install: ";
			cin >> Num;
			cin.ignore();
			cout << endl << endl;
			for (int i = 0; i < Num; i++)
			{
				Bus a;
				a.Install();
				_bus.push_back(new Bus(a));
				system("pause");
				system("cls");
				
				Draw("AdminSetup");
			}
			cout << endl;
			system("pause");
			system("cls");

			break;
		}
		case 2:
		{
			Draw("AdminSetup");
			int Num;
			cout << "Enter number bus you want to Install: ";
			cin >> Num;
			cin.ignore();
			cout << endl << endl;
			for (int i = 0; i < Num; i++)
			{
				Bed_Car b(i + 1);
				b.Install();
				addBed_car(b);
				system("pause");
				system("cls");

				Draw("AdminSetup");
			}

			cout << endl;
			system("pause");
			system("cls");

			break;
		}
		case 3:
		{
			Draw("AdminSetup");
			int Num;
			cout << "Enter number bus you want to Install: ";
			cin >> Num;
			cin.ignore();
			for (int i = 0; i < Num; i++)
			{
				VIP c(i + 1);
				c.Install();
				addVip(c);
				system("pause");
				system("cls");

				Draw("AdminSetup");
			};

			cout << endl;
			system("pause");
			system("cls");
			break;
		}
		case 4:
		{
			Draw("AdminSetup");
			int Num;
			cout << "Enter number of bus which you want to Install: ";
			cin >> Num;
			cin.ignore();
			cout << endl << endl;
			for (int i = 0; i < Num; i++)
			{
				SuperVip d(i + 1);
				d.Install();
				addVipCar(d);
				system("pause");
				system("cls");

				Draw("AdminSetup");
			}

			cout << endl;
			system("pause");
			system("cls");

			break;
		}
		}
	}
}

void BusStation::Rev()
{
	int Bus_no;
	cout << "CUSTOMER: " << endl;
	cout << "Buses availabile: " << endl;
top1:
	for (int i = 0; i < _bus.size(); i++)
	{
		_bus[i]->Show();
		cout << endl;
	}
	cout << endl;
	cout << "Enter Bus No: ";
	cin >> Bus_no;
	cin.ignore();
	for (int i = 0; i < _bus.size(); i++)
	{
		if (_bus[i]->Number == Bus_no)
		{
			_user[_user.size() - 1].setTypeOfBus(_bus[i]->getTypeOfBus());
			_user[_user.size() - 1].setNameOfTrip(_bus[i]->getNameOfTrip());
			system("cls");
			_bus[i]->ShowSeat();
			_bus[i]->Reserve(_user[_user.size()-1]);
			system("pause");
			system("cls");
			_bus[i]->ShowSeat();
			system("pause");
			break;
		}
		else
		{
			continue;
		}
	}

}

void BusStation::showBus()
{
	cout << "Buses availabile: " << endl;
	for (int i = 0; i < _bus.size(); i++)
	{
		_bus[i]->Show();
		cout << endl;
	}
}

//Admin
void Admin::setUsername(string str)
{
	_username = str;
}

void Admin::setPassword(string str)
{
	_password = str;
}

string Admin::getUsername()
{
	return _username;
}

string Admin::getPassword()
{
	return _password;
}

void BusStation::addBed_car(Bed_Car a)
{
	_bus.push_back(new Bed_Car(a));
}

void BusStation::addVip(VIP b)
{
	_bus.push_back(new VIP(b));
}

void BusStation::addVipCar(SuperVip c)
{
	_bus.push_back(new SuperVip(c));
}

void BusStation::CustomerMenu(){

	int choiceForAdmin = 0, choiceForUser = 0, role = 0;

	while (role != 3) {
		Draw("BUS RESERVATION SYSTEM ");
		GotoXY(50, 4);
		cout << "1. User " << endl;
		GotoXY(50, 6);
		cout << "2. Admin " << endl;
		GotoXY(50, 8);
		cout << "3. Exit " << endl;
		GotoXY(50, 10);
		cout << "Your choice: ";
		cin >> role;

		if (role == 3) {
			break;
		} 
		else if (role == 1) {
			system("cls");
			while (choiceForUser != 4) {
				Draw("User Reservation");
				GotoXY(50, 4);
				cout << "1. Book Ticket(s) " << endl;
				GotoXY(50, 10);
				cout << "2. Show Information Of Ticket(s) " << endl;
				GotoXY(50, 12);
				cout << "3. Add Feedback " << endl;
				GotoXY(50, 14);
				cout << "4. Exit " << endl;
				GotoXY(50, 16);
				cout << "Your choice: ";
				cin >> choiceForUser;

				switch (choiceForUser) {
				case 1:
					system("cls");
					Draw("Customer Reservation");
					addUser();
					system("cls");
					Rev();
					break;
				case 2:
					system("cls");
					showTicketOfUser();
					system("pause");
					break;
				case 3:
					system("cls");
					break;
				default:
					break;
				};
				system("cls");
			}
			system("pause");
		} 
		else if (role == 2) {
			system("cls");
			setAdmin();
			if (logInForAdmin()) {
				system("cls");
				while (choiceForAdmin != 5) {
					Draw("Admin Setup");
					GotoXY(50, 4);
					cout << "1. Add Bus " << endl;
					GotoXY(50, 6);
					cout << "2. Show Information Of Bus(es) " << endl;
					GotoXY(50, 8);
					cout << "3. Show Information Of Passenger(s) " << endl;
					GotoXY(50, 10);
					cout << "4. Log Out " << endl;
					GotoXY(50, 12);
					cout << "5. Exit" << endl;
					GotoXY(50, 14);
					cout << "Your choice: ";
					cin >> choiceForAdmin;
					switch (choiceForAdmin) {
					case 1:
						system("cls");
						AddCar();
						break;
					case 2:
						system("cls");
						showBus();
						system("pause");
						break;
					case 3:
						system("cls");
						showPassenger();
						system("pause");
						break;
					case 4:
						system("cls");
						break;
					default:
						break;
					};
					system("cls");
				}
			}
			system("pause");
		}
		system("cls");
	}
	system("cls");
}