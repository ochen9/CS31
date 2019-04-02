#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
	
	//declaring variables
	string importer = "";
	string product = "";
	double product_value = 0;
	double import_duty = 0;
	
	
	cout << "Importer: ";
	getline(cin, importer);
	if(importer=="")//case of empty string input for importer name
		cout<<"You must enter an importer."<<endl;
	
	cout << "Product value (in trillions): ";
	cin >> product_value;
	cin.ignore(100,'\n'); //done entering input when new line character is recognized
	if(product_value<0) //case of negative input
		cout<<"The product value must not be negative."<<endl;
	
	cout <<"Product: ";
	getline(cin, product);
	if(product=="") //case of empty string input for product
		cout<<"You must enter a product."<<endl;
	
	

	
	
	//first 500 trillion grubnicks
	if(product_value<=500)
		import_duty = 0.31*product_value;
	//500-900 trillion and not pigs or mud
	if(product_value>500 && product_value<=900 && product!="pigs" && product!="mud")
	{
		import_duty = 0.31*(500) + 0.25*(product_value-500);
	}
	//500-900 trillion with pigs or mud
	else if(product_value>500 && product_value<=900 && (product=="pigs" || product=="mud"))
	{
		import_duty = 0.31*(500) + 0.29*(product_value-500);
	}
	//over 900 trillion and not pigs or mud
	else if (product_value>900 && product!="pigs" && product!="mud")
	{
		import_duty = 0.31*(500) + 0.25*(400) +0.22*(product_value-900);
	}
	//over 900 trillion with pigs or mud
	else if (product_value>900 && product!="pigs" && product!="mud")
	{
		import_duty = 0.31*(500) + 0.29*(400) +0.22*(product_value-900);
	}
	
	cout<<"\n"<<"---"<<"\n"<<endl;//3 hyphens
	cout << "The import duty for "<<importer<<" is G"<<fixed<<setprecision(2)<<import_duty<<" trillion."<<endl;
	 //fixed and setprecision is to make sure that there are 2 decimal points filled in the import duty
}
	 
