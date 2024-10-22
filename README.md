# Bank-Management-C-
Select and Download the correct amalgamation .zip file corresponding to your Operating System.
The sqlite source code used for the project will be available.

**Running on Linux Terminal**:
```
    ~$ g++ source_code.. -o output_file -lpthread -ldl -lsqlite
    ~$ ./output_file
    example:
    ~$ g++ bankRun.cpp UTILS/utils.cpp -o bank -lpthread -ldl -lsqlite
    ~$ ./bank
```

**Program File Structure (Architecture)**
```
Bank-Management-C-/
├── bankRun.cpp
├── UTILS/
│   ├── sqlite3.c
│   ├── utils.h
│   ├── utils.cpp
│   └── bank_db.db
├── compiled/
│   └── bank
├── README.md
└── LICENSE
```

**Features**
```
1. Create Account
2. Delete Account
3. Login to Account
4. Admin Login
5. Credit Account
6. Send money to a User
```
**Note**: compiled file is already given file permission..

*Program still in development...*
*Report bugs to my media account.*

