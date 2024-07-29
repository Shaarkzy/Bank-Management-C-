
#include <iostream>
#include <sqlite3.h>
#include <string>
#include "UTILS/utils.h"
using namespace std;

/*
bool containsText(const string& input) {
    for (char c : input) {
        if (!isdigit(c)) { // if character is not a digit
            return true; // contains text
        }
    }
    return false; // only digits
}*/


sqlite3* db;
int rc;
void check()
{
        rc = sqlite3_open("UTILS/bank_db.db", &db);
	int rc = sqlite3_open("UTILS/bank_db.db", &db);
	if (rc != SQLITE_OK)
	{
                cout << endl;
		cout << "[@]::Can't Open Database: " << sqlite3_errmsg(db) << endl;
	}
	else
	{
                cout << "\n\n";
		cout << string(65 ,'=') << endl;
		cout << string(20, ' ') <<  "[@] Database Initiated Successfully...✓ " << endl;
		cout << string(65, '=') << endl;
		 
	}
}



//Create a Table
void create_table()
{
	const char* createTablequery = " CREATE TABLE IF NOT EXISTS Bank(id INTEGER PRIMARY KEY, acc_n INTEGER, password INTEGER, secret TEXT, amount INTEGER);";
	rc = sqlite3_exec(db, createTablequery, 0, 0, 0);
	if (rc != SQLITE_OK)
	{
		cout << "[@]::Error Creating Table: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
	}
	else
	{
		cout << string(25, ' ') << "[@]::Table created ..✓ " << endl;
		 
		cout << string(65, '=') << endl;

	}
}

bool check_user(int account)
{
	sqlite3_stmt* stmt;
	string checkQuery = "SELECT * FROM Bank WHERE acc_n = '" + to_string(account)+ "';";
	rc = sqlite3_prepare_v2(db,checkQuery.c_str(), -1, &stmt, nullptr);

	if (rc == SQLITE_OK)
	{
		if (sqlite3_step(stmt) == SQLITE_ROW)
		{
			return false;
			sqlite3_close(db);
		}
		else
		{
			return true;
			sqlite3_close(db);
		}
	}
	else
	{
		return true;
	}
}




void add_user(int account, int pass, string secret_word, int amount)
{
	if (check_user(account))
	{
	    string insertQueryString = "INSERT INTO Bank(acc_n, password, secret, amount) VALUES ('"+to_string(account)+"','"+to_string(pass)+"','"+secret_word+"','"+to_string(amount)+"');";
            const char* insertQuery = insertQueryString.c_str();

            rc = sqlite3_exec(db, insertQuery, 0, 0, 0);
            if (rc != SQLITE_OK)
	    {
		    cout << "[@]::Insertion failed: " << sqlite3_errmsg(db) << endl;
		    sqlite3_close(db);
	    }
	    else
	    {
		    cout << string(65, '=') << endl;
		    cout << string(20, ' ') << "[@]::Sign Up Successfull..✓" << endl;
	             
		    cout << string(65, '=') << endl;
                    sqlite3_close(db);
		
	    }
	}
	else
	{
	    cout << string(65, '=') << endl;
	    cout << "[x]::Account Number Already Exist" << endl;
	    cout << string(65, '=') << endl;
	    sqlite3_close(db);

	}
}



bool send(int accn, int amount, int account)
{
	if (accn == account){
		cout << string(65, '=') << endl;
		cout << "Error, invalid account" << endl;
		cout << string(65, '=') << endl;
		sqlite3_close(db);
		return false;
	}
	else{
        sqlite3_stmt* stmt1;
        string loginQuery = "SELECT * FROM Bank WHERE acc_n = '" +to_string(accn)+ "';";
        rc = sqlite3_prepare_v2(db, loginQuery.c_str(), -1, &stmt1
, nullptr);

        if (rc == SQLITE_OK)
        {
			if (sqlite3_step(stmt1) == SQLITE_ROW)
			{
			    int money = sqlite3_column_int(stmt1, 4);
                            int total = money + amount;

                            string updateHost = "UPDATE Bank SET amount ="+ to_string(total) +" WHERE acc_n ='"+to_string(accn)+"';";

                            const char* update = updateHost.c_str();
                            rc = sqlite3_exec(db, update, 0, 0, 0);

                            if (rc == SQLITE_OK)
                             { 
				    cout << string(65, '=') << endl;
                                    cout << "[✓]::Transanction Succesfull.." << endl;
				    cout << string(65, '=') << endl;
				    return true;
				    sqlite3_close(db);
			
                             }
                            else
                            {
                                    cout << "[x]::Error" << sqlite3_errmsg(db) << endl;
				    sqlite3_close(db);
				    return false;
				
                            }
		         }//int mo = stoi(new_money);
		         else
		         {
			     cout << string(65, '=') << endl;	 
		             cout << "[x]::Account Doesnt Exist" << endl;
			     cout << string(65, '=') << endl;
			     return false;
			     sqlite3_close(db);
			
		         }

                
	}
	else
	{
		cout << sqlite3_errmsg(db);
		return false;
		sqlite3_close(db);
		
	}
	}


}















//User Transaction
void transaction(int account)
{
	cout << string(20, ' ') << endl;
	cout << string(65, '=') << endl;
	cout << "[@]::Add money[1] or Send[2]: ";
	string choose;
	cin >> choose;
	cout << string(65, '=') << endl;
	if (containsText(choose)){
	    //cin.clear();
	    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    cout << "[x]::Error, text not allowed" << endl;
	    cout << string(65, '=') << endl;
	    sqlite3_close(db);
	    
	}
	else{
	sqlite3_stmt* stmt1;
        string loginQuery = "SELECT * FROM Bank WHERE acc_n = '" + to_string(account)+ "';";
        rc = sqlite3_prepare_v2(db, loginQuery.c_str(), -1, &stmt1, nullptr);
        int amount; int init_money; string new_money; string host;

	if (rc == SQLITE_OK)
	{
		while (sqlite3_step(stmt1) == SQLITE_ROW)
		{
                    init_money = sqlite3_column_int(stmt1, 4);
		    if (choose == "1")
		    {
			    cout << string(65, '=') << endl;
			    cout << "[@]::Balance: " << init_money<< endl;
			    cout << string(65, '=') << endl;
			    cout << "[@]::Amount To Credit: ";
			    cin >> new_money;
			    if (containsText(new_money)){
			    //cin.clear();
			    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
			    cout << string(65, '=') << endl;
			    cout << "[x]::Error, alphabet not allowed" << endl;
			    cout << string(65, '=') << endl;
			    sqlite3_close(db);
			    //break;
			    }
			    else{
			    //int mo = stoi(new_money);
			    amount = init_money + stoi(new_money);

		    }
		    } /*
		    else if (choose == "2")
		    {
			    cout << "[@]::Balance: " << init_money << endl;
			    cout << "[@]::Amount To debit: ";
			    cin >> new_money;
			    if (containsText(new_money)){
			    //cin.clear();
			    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
			    cout << "errror" << endl;
			    break;
			    }
			    else{
			    int mo = stoi(new_money);
			    amount = init_money - mo;
			    }
		    } */
		    else if (choose == "2")
		    {
			    cout << "[@]::Balance: " << init_money<< endl;

			    //string host;
			    cout << "[@]::Account Number: ";
			    cin >> host;
			    if (containsText(host)){
			    //cin.clear();
			    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
			    cout << string(65, '=') << endl;
			    cout << "[x]::Error, alphabet not allowed" << endl;
			    cout << string(65, '=') << endl;
			    sqlite3_close(db);
			    }
			    else{
			    int ho = stoi(host);

			    cout << "[@]::Amount: ";
			    cin >> new_money;
			    if (containsText(new_money)){
			    //cin.clear();
			    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
			    cout << string(65, '=') << endl;
			    cout << "[x]::Error, alphabet not allowed" << endl;
			    cout << string(65, '=') << endl;
			    sqlite3_close(db);
			    }
			    else{
			    int mo = stoi(new_money);
			    int tol1 = init_money - mo;

			    if (tol1 < 0)
			    {
				    cout << string(65, '=') << endl;
				    cout << "[x]::Insufficient Fund" << endl;
				    cout << string(65, '=') << endl;
				    amount = init_money;
				    sqlite3_close(db);


			    }
			    else
			    {
				    int ho = stoi(host);
				    int mo = stoi(new_money);
				    if (send(ho, mo, account))
				    {
					    int mo = stoi(new_money);
					    amount = init_money - mo;
					    sqlite3_close(db);
				       
				    }
				    else
				    {
					    amount = init_money;
					    sqlite3_close(db);
				    }
			    }
			    }
			    }
		    }
		
	

                    if (containsText(new_money) || containsText(host)){
				continue;
				sqlite3_close(db);
				}
		else{
	            string updateQueryString = "UPDATE Bank SET amount ="+ to_string(amount) +" WHERE acc_n = '"+to_string(account)+"';";
                    const char* updateQuery = updateQueryString.c_str();
	            rc = sqlite3_exec(db, updateQuery, 0, 0, 0);
	            if (rc != SQLITE_OK)
	            {
			cout << string(65, '=') << endl;
                        cout << "[x]::Transaction Failed " << sqlite3_errmsg(db) << endl;
			cout << string(65, '=') << endl;
			sqlite3_close(db);
	            }
	            else
	            {
			cout << string(65, '=');
                        cout << string(20, ' ') <<  "[@]::Transaction Completed" << endl;
			cout << string(65, '=') << endl;
			sqlite3_close(db);
	            }
		    
		}
		}
	}
         
         else{
		 cout << string(65, '=') << endl;
		 cout << "[x]::An Error Occured.." << sqlite3_errmsg(db) <<  endl;
		 cout << string(65, '=') << endl;
		 sqlite3_close(db);
                
         }
	}
	
}
	 




//Buggy code, should'nt be runned, left here for some reasons i dont know.., anaylse and see why.
/*void send(int accn, int amount)
{
	sqlite3_stmt* stmt1;                                              string loginQuery = "SELECT * FROM Bank WHERE acc_n = '" +to_string(accn)+ "';";
        rc = sqlite3_prepare_v2(db, loginQuery.c_str(), -1, &stmt1
, nullptr);

	if (rc == SQLITE_OK)
	{
		while(sqlite3_step(stmt1) == SQLITE_ROW)
		{
			int money = sqlite3_column_int(stmt1, 4);
			int total = money + amount;

			string updateHost = "UPDATE Bank SET amount ="+ to_string(total) +" WHERE acc_n = '"+to_string(accn)+"';";

			const char* update = updateHost.c_str();
			rc = sqlite3_exec(db, update, 0, 0, 0);

			if (rc == SQLITE_OK)
			{
				cout << "Done" << endl;
			}
			else
			{
				cout << "Error 1" << sqlite3_errmsg(db) << endl;
			}





		}

	}


}*/






//Delete Registered Account
void delete_user(int account, int pass)
{
	string  deleteQueryString = "DELETE FROM Bank WHERE acc_n = '"+to_string(account)+"'" +" AND password ='"+to_string(pass)+"';";
        const char* deleteQuery = deleteQueryString.c_str();
	rc = sqlite3_exec(db, deleteQuery, 0, 0, 0);
	if (rc != SQLITE_OK)
	{
		cout << "[x]::Deletion Failed: " << sqlite3_errmsg(db) <<  endl;
		sqlite3_close(db);
	}
	else
	{
		cout << string(65, '=') << endl;
		cout << string(20, ' ') << "[✓]::Deleted .." << endl;
		cout << string(65, '=') << endl;
		sqlite3_close(db);
	
	}

}

//Login to registered account
void login(int account, int pass)
{
	string loginQuery = "SELECT * FROM Bank WHERE acc_n = '"+to_string(account)+"';";
     
	sqlite3_stmt* stmt;
        rc = sqlite3_prepare_v2(db, loginQuery.c_str(), -1, &stmt, nullptr);


	if (rc == SQLITE_OK)
	{
            
		if (sqlite3_step(stmt) == SQLITE_ROW)
		{
		    int acc = sqlite3_column_int(stmt, 1);
		    int password = sqlite3_column_int(stmt, 2);

		    if ( acc == account && pass == password)
	            {
			    cout << string(65, '=') << endl;
			    cout << "[✓]::Verified User....✓" << endl;
			    cout << string(65, '=') << endl;
			    cout << "[@]::Transaction[1] or Delete Account[2]: ";
			    string choose;
			    cin >> choose;
			    cout << string(65, '=') << endl;
			    if (containsText(choose)){
				    cout << string(65, '=') << endl;
				    cout << "[x]::Error, alphabet not allowed" << endl;
				    cout << string(65, '=') << endl;
				    sqlite3_close(db);
			    }
			    else{
			    
			    if (choose == "1")
			    {
				    transaction(acc);
				    sqlite3_close(db);
			    }
			    else if (choose == "2")
			    {
				    delete_user(acc , password);
				    sqlite3_close(db);
			    }
			    }
			    
		    }
		    else if (acc == account && pass != password)
		    {
			    cout << string(65, '=') << endl;
			    cout << "[x]::Incorect Password" << endl;
			    cout << string(65, '=') << endl;
			    cout << "Try recovering your account By inputing your secret text: ";
			    //cout << string(65, '=') << endl;
			    string sec;
			    cin >> sec;
			    //cout << string(65, '=') << endl;
			    const char* secret = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
			    if (sec == secret)
			    {
				    cout << string(65, '=') << endl;
				    cout << "[✓]::Verified...✓\n[=] Your password is:" << password << endl;
				    cout << string(65, '=') << endl;
				    sqlite3_close(db);
				    
			    }
			  
			    else
			    {
				    cout << string(65, '=') << endl;
				    cout << "[x]::Invalid ..x" << endl;
				    cout << string(65, '=') << endl;
				    sqlite3_close(db);
			    }
			    
		    }
		    else
		    {
			    cout << string(65, '=') << endl;
			    cout << "[x]::Not verified...x" << endl;
			    cout << string(65, '=') << endl;
			    sqlite3_close(db);
		    }
		    
		}
		else
		{
			cout << string(65, '=') << endl;
			cout << "[x]::Accout Doesnt exist" << endl;
			cout << string(65, '=') << endl;
			sqlite3_close(db);
		}
	}

        else
  	{
	    cout << string(65, '=') << endl;
            cout << "[x]::An Error occured: " << sqlite3_errmsg(db) << endl;
	    cout << string(65, '=') << endl;
	    sqlite3_close(db);
        
	}

}









//Display Users in Database
void print()
{
	const char* printQuery = " SELECT * FROM Bank;";
	sqlite3_stmt* statement;
	rc = sqlite3_prepare_v2(db, printQuery, -1, &statement, nullptr);
	if (rc == SQLITE_OK)
	{
                int t = 65; int e = t/5;
                int len_i = sizeof("ID");
                int len_a = sizeof("ACCOUNT");
                int len_p = sizeof("PASSWORD");
                int len_am = sizeof("AMOUNT");
                int len_s = sizeof("SECRET");

                int div_i = ((e - len_i) /2);
                int div_a = ((e - len_a) /2);
                int div_p = ((e - len_p) /2);
                int div_am = ((e - len_am) /2);
                int div_s = ((e - len_s) /2);

                string out_i = string(div_i, ' ');
                string out_a = string(div_a, ' ');
                string out_p = string(div_p, ' ');
                string out_am = string(div_am, ' ');
                string out_s = string(div_s, ' ');

                cout << string(65, '=') << endl;
                cout << out_i <<"ID  |" << out_i << out_a <<"ACCOUNT |" << out_a << out_p <<"PASSWORD |" << out_p << out_am <<"AMOUNT |" << out_am << out_s <<"SECRET" << out_s << endl;

		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			int id = sqlite3_column_int(statement, 0);
			const char* secret = reinterpret_cast<const char*>(sqlite3_column_text(statement, 3));
			int account = sqlite3_column_int(statement, 1);
			int passwd = sqlite3_column_int(statement, 2);
			int amount = sqlite3_column_int(statement, 4);
			int total; int each;

			total = 65; //screen width character length
			each = total / 5;

			cout << string(65, '=') << endl;

			int len_id = sizeof(id);
			int len_acc = sizeof(account);
			int len_pass = sizeof(passwd);
			int len_am = sizeof(amount);
			int len_sec = sizeof(secret);

			int div_id = ((each - len_id) / 2);
			int div_acc = ((each - len_acc) / 2);
			int div_pass = ((each - len_pass) / 2);
			int div_am = ((each - len_am) / 2);
			int div_sec = ((each - len_sec) /  2);

			string out_id = string(div_id, ' ');
			string out_acc = string(div_acc, ' ');
			string out_pass = string(div_pass, ' ');
			string out_am = string(div_am, ' ');
			string out_sec = string(div_sec, ' ');

			cout << out_id << id << "  |" << out_id << out_acc << account << "  |" <<  out_acc << out_pass << passwd << "  |" << out_pass << out_am << amount << "  |" <<  out_am << out_sec << secret << out_sec << endl;

                }
                cout << string(65, '=') << endl;
		sqlite3_close(db);
        }
}
//Edit your ADMIN name and password
void admin()
{
	string name; string pass;
	cout << "[@]::Admin: ";
	cin >> name;
	cout << "[@]::Pass: ";
	cin >> pass;
	//cout << string(65, '=') << endl;

	if (containsText(pass)){
		//cin.clear();
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << string(65, '=') << endl;
		cout << "[x]::Error, alphabet not allowed" << endl;
		cout << string(65, '=') << endl;
		
	}
	else{
	if (name == "SHARK" && pass == "2003")
	{
		cout << string(65, '=') << endl;
                cout << string(25, ' ') << "[✓]::Logged In As Admin.." << endl;
		cout << string(65, '=') << endl;

		print();
	}
	else
	{
		cout << string(65, '=') << endl;
		cout << "[x]::Wrong Credentials.." << endl;
		cout << string(65, '=') << endl;
		
	}
	}
}





//Run the whole code selected
int main ()
{
	check();
        create_table();
	//int i;
	while (2 ==  2) 
	{
	try {

	    cout << "[@]::Admin Login [1]: user:SHARK:pass:2003 \n[@]::Sign Up [2] \n[@]::Sign In [3]\n[-]: ";
	    string num;
            string account; string password; string amount; string secret;
	    cin >> num;
	    cout << string(65, '=') << endl;
		    if (num == "1"){
			    admin();
			    }
		    else if(num == "2"){
                            cout << string(65, '=');
                            cout << string(25, ' ') << "[@]::SIGN UP " << endl;
                            cout << "[@]::Account Number: ";
                            cin >> account;
			    if (containsText(account)){
				    cout << string(65, '=') << endl;
				    cout << "[x]::Error, alphabet not allowed" << endl;
				    cout << string(65, '=') << endl;
				    //break;
			    }
			    else{
			    int acc = stoi(account);
			    cout << "[@]::4 digit Password: ";
			    cin >> password;
			    if (containsText(password)){
				    cout << string(65, '=') << endl;
				    cout << "[x]::Error, alphabet not allowed" << endl;
				    cout << string(65, '=') << endl;
				    //break;
			    }
			    else{
			    int pass = stoi(password);
                            cout << "[@]::Amount to Credit: ";
                            cin >> amount;
			    if (containsText(amount)){
				    cout << string(65, '=') << endl;
				    cout << "[x]::Error, alphabet not allowed" << endl;
				    cout << string(65, '=') << endl;
				    //break;
			    }
			    else{
	                    int am = stoi(amount);
			    cout << "[@]::Secret text for password Recovery: ";
			    cin >> secret;
			    add_user(acc, pass, secret, am);
			    //break;
			    }
			    }
			    }
		    }
		    else if(num == "3"){
                            cout << string(65, '=') << endl;
                            cout << "[@] SIGN IN" << endl;
			    cout << "[@]::Account: ";
			    cin >> account;
			    if (containsText(account)){
				    cout << string(65, '=') << endl;
				    cout << "[x]::Error, alphabet not allowed" << endl;
				    cout << string(65, '=') << endl;
				    //break;
			    }
			    else{
			    int acc = stoi(account);	    
			    cout << "[@]::4 digit Password: ";
			    cin >> password;
			    if (containsText(password)){
				    cout << string(65, '=') << endl;
				    cout << "[x]::Error, alphabet not allowed" << endl;
				    cout << string(65, '=') << endl;
				    //break;
			    }
			    else{
			    int pass = stoi(password);
			    login(acc, pass);
			    //break;
			    }
			    }
		    }
            
		}catch(...){
			cout << string(65, '=') << endl;
			cout << "[x]::An error occured" << endl;
			cout << string(65, '=') << endl;
			//break;
		
	    
        }
	}




	return 0;
}

