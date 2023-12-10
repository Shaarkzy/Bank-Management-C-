
#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std;


sqlite3* db;
int rc;
void check()
{
        rc = sqlite3_open("bank_db.db", &db);
	int rc = sqlite3_open("bank_db.db", &db);
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
	    }
	    else
	    {
		    cout << string(65, '=') << endl;
		    cout << string(20, ' ') << "[@]::Sign Up Successfull..✓" << endl;
		    cout << string(65, '=') << endl;
		
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



bool send(int accn, int amount)
{
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
                                    cout << "Error 1" << sqlite3_errmsg(db) << endl;
				    return false;
				
                            }
		         }
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
		
	}


}















//User Transaction
void transaction(int account)
{
	cout << string(20, ' ') << endl;
	cout << string(65, '=') << endl;
	cout << "[@]::Add money[1] or Receive[2] or Send[3]: ";
	int choose;
	cin >> choose;
	sqlite3_stmt* stmt1;
        string loginQuery = "SELECT * FROM Bank WHERE acc_n = '" + to_string(account)+ "';";
        rc = sqlite3_prepare_v2(db, loginQuery.c_str(), -1, &stmt1, nullptr);
        int amount; int init_money; int new_money;

	if (rc == SQLITE_OK)
	{
		while (sqlite3_step(stmt1) == SQLITE_ROW)
		{
                    init_money = sqlite3_column_int(stmt1, 4);
		    if (choose == 1)
		    {
			    cout << string(65, '=') << endl;
			    cout << "[@]::Balance: " << init_money<< endl;
			    cout << string(65, '=') << endl;
			    cout << "[@]::Amount To Credit: ";
			    cin >> new_money;
			    amount = init_money + new_money;

		    }
		    else if (choose == 2)
		    {
			    cout << "[@]::Balance: " << init_money << endl;
			    cout << "[@]::Amount To debit: ";
			    cin >> new_money;
			    amount = init_money - new_money;
		    }
		    else if (choose == 3)
		    {
			    cout << "[@]::Balance: " << init_money<< endl;

			    int host;
			    cout << "[@]::Account Number: ";
			    cin >> host;
			    cout << "[@]::Amount: ";
			    cin >> new_money;

			    int tol1 = init_money - new_money;

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
				    if (send(host, new_money))
				    {
					    amount = init_money - new_money;
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
	




				    



	            string updateQueryString = "UPDATE Bank SET amount ="+ to_string(amount) +" WHERE acc_n = '"+to_string(account)+"';";
                    const char* updateQuery = updateQueryString.c_str();
	            rc = sqlite3_exec(db, updateQuery, 0, 0, 0);
	            if (rc != SQLITE_OK)
	            {
			cout << string(65, '=') << endl;
                        cout << "[x]::Transaction Failed..: " << sqlite3_errmsg(db) << endl;
			cout << string(65, '=') << endl;
	            }
	            else
	            {
			cout << string(65, '=');
                        cout << string(20, ' ') <<  "[@]::Transaction Completed..✓ .." << endl;
			cout << string(65, '=') << endl;
			sqlite3_close(db);
	            }
		    
		}
         
         else
         {
                cout << "[x]::An Error Occured.." << sqlite3_errmsg(db) <<  endl;
                
         }
	 

}


//Code wont work Function Exist after Transaction
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


}
*/





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
		cout << string(65, '=');
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
			    int choose;
			    cin >> choose;
			    if (choose == 1)
			    {
				    transaction(acc);
			    }
			    else if (choose == 2)
			    {
				    delete_user(acc , password);
			    }
			    
		    }
		    else if (acc == account && pass != password)
		    {
			    cout << string(65, '=') << endl;
			    cout << "[x]::Incorect Password" << endl;
			    cout << string(65, '=') << endl;
			    cout << "Try recovering your account By inputing your secret text: ";
			    string sec;
			    cin >> sec;
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
            cout << "[x]::An Error occured: " << sqlite3_errmsg(db) << endl;
        
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

			total = 65;
			each = total / 5;

			cout << string(65, '=');

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
        }
}
//Edit your ADMIN name and password
void admin()
{
	string name; int pass;
	cout << "[@]::Admin: ";
	cin >> name;
	cout << "[@]::Pass: ";
	cin >> pass;
	if (name == "SHARK" && pass == 2003)
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





//Run the whole code selected
int main ()
{
	check();
        create_table();
	while (2 == 2)
	{

	    cout << "[@]::Admin Login [1] \n[@]::Sign Up [2] \n[@]::Sign In [3]: ";
	    int num;
            int account; int password; int amount; string secret;
	    cin >> num;
	    switch (int x = num)
	    {
		    case 1:
			    admin();
			    break;
		    case 2:
                            cout << string(65, '=');
                            cout << string(25, ' ') << "[@] SIGN UP " << endl;
                            cout << "[@]::Account Number: ";
                            cin >> account;
			    cout << "[@]::4 digit Password: ";
			    cin >> password;
                            cout << "[@]::Amount to Credit: ";
                            cin >> amount;
			    cout << "[@]::Secret text for password Recovery: ";
			    cin >> secret;
			    add_user(account, password, secret, amount);
			    break;
		    case 3:
                            cout << string(65, '=') << endl;
                            cout << "[@] SIGN IN" << endl;
			    cout << "[@]::Account: ";
			    cin >> account;
			    cout << "[@]::4 digit Password: ";
			    cin >> password;
			    login(account, password);
			    break;
            }
        }



	return 0;
}













