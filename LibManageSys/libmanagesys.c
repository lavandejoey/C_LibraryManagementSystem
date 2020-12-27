#include<ctype.h>
#include<dos.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
void addBooks(void);//finished
void adminiMainMenu(void);//finished
void borrowBooks(void);
void changeNum(int i);//finished
void closeApplication(void);//finished
void deleteBooks(void);//finished
void editBooks(void);//finished
void loadingAnim(void);//finished
void passWord(void);//finished
void previewPage(void);//finishe
void returnBooks(void);
void returnfunc(void);//finished
void searchBooks(void);//finished
void searchBookID();//finished
void searchBookName();//finished
void userMainMenu(void);//finished
void viewBooks(void);//finished
void wrongEnter(int i);//finished
int getdata(int i);//finished
int checkid(int t);//finished
int searchID(int t);
void logIn(void);//finished
void signIn(void);//finished
void signUp(void);//finished
void writeUserData(void);//finished
void viewUsers(void);
int sysFlag = -1;//recognize admini/user
char catagories[10][15] = { "Computer","Electronics","Electrical","Civil","Mechanical","Architecture", "Art", "Others" };
char passwordUser[20] = { "000000" };
char passwordAdmini[20] = { "123456" };
struct books {
    char catag[15];//图书分类的地址
    int bookID;//图书编号
    char bookName[20];//图书名
    char authorName[20];//作者名
    int quantity;//数量
}book, bookTrans;
struct users {
    char id[100];
    char unserName[100];
    char pwd[100];//password
    int borrowedBookNum;
}user, userTrans;
FILE* fp, * ft, * fu;//point of file
COORD coord = { 0, 0 };
void gotoxy(int x, int y) {
    coord.X = x;
    coord.Y = y; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}//光标的初始位置设置
int main(void) {
    previewPage();//page for welcom
    return 0;
}//主函数（看起来好简陋）
void previewPage(void) {
    system("cls");//清屏
    char start[] = "Welcome for Using ECUST Library Management System";
    gotoxy(10, 10);
    for (int i = 0; i < 15; i++) {
        Sleep(50); //delay the action
        printf(":");
    }
    for (int i = 0; i <= strlen(start); i++) {
        Sleep(50);
        printf("%c", start[i]);
    }
    for (int i = 0; i < 15; i++) {
        Sleep(50);
        printf(":");
    }//输出欢迎语
    Sleep(1000);
    passWord();//输入系统密码界面
}//page for welcom
void loadingAnim() {
    for (int i = 0; i < 3; i++) {
        system("cls");
        gotoxy(20, 10);
        char w[] = "LOADING........";
        for (int loader = 0; loader < 10; loader++) {
            Sleep(100);
            printf("%c", w[loader]);
        }//文字滚动
        Sleep(50);
    }
}//加载页面
void passWord(void) {
    system("cls");
    char d[25] = "Enter The System Password";
    char ch = '\0', pass[10]; int i = 0, j;
    gotoxy(10, 4);
    for (j = 0; j < 16; j++) {
        Sleep(50);
        printf(":");
    }
    for (j = 0; j < 25; j++) {
        Sleep(50);
        printf("%c", d[j]);
    }
    for (j = 0; j < 16; j++) {
        Sleep(50);
        printf(":");
    }//输出标题
    gotoxy(15, 7); printf("(If you are not Administrator,please print'000000')");
    gotoxy(15, 8); printf("Enter Password:");//输出提示语
    while (ch != 13) {//not ENTER
        ch = getch();
        if (ch >= 32 && ch <= 126) {//letter and num
            putch('*');
            pass[i] = ch;
            i++;
        }
    }//输入密码，存储
    pass[i] = '\0';
    if (strcmp(pass, passwordUser) == 0) {//密码比对，用户端
        gotoxy(15, 10); printf("Now You Are Logged In!");
        gotoxy(15, 12); printf("===>Press any key to countinue...");
        getch(); logIn();//进入用户端登录注册页
    }//用户系统
    else if (strcmp(pass, passwordAdmini) == 0) {//密码比对，管理端
        gotoxy(15, 10); printf("Now You Are Logged In (Administration Mode)!");
        gotoxy(15, 12); printf("===>Press any key to countinue...");
        getch(); adminiMainMenu();
    }//管理员系统
    else {
        gotoxy(15, 16); printf("\aWarning!!! Incorrect Password!");
        getch(); passWord();//重新输入
    }//密码错误
}//登陆界面
void userMainMenu(void) {
    sysFlag = 0;//标记为用户端
    loadingAnim();//加载页面
    system("cls");//清屏
    gotoxy(20, 2); printf("HELLO %s", user.unserName);
    gotoxy(20, 3); printf("::::::: LIBRARY MANAGEMENT SYSTEM :::::::");
    gotoxy(25, 5); printf("1==> Search Books");
    gotoxy(25, 7); printf("2==> View Books List");
    gotoxy(25, 9); printf("3==> Borrow Books");
    gotoxy(25, 11); printf("4==> Return Books");
    gotoxy(25, 13); printf("5==> Log Out");
    gotoxy(25, 15); printf("6==> Administrator Login");
    gotoxy(25, 17); printf("7==> Close the Application");
    gotoxy(20, 19); printf(":::::::::::::::::::::::::::::::::::::::::");//菜单栏
    gotoxy(20, 21); printf("Enter your choice:");
    switch (getch()) {
    case '1': searchBooks(); break;//查找图书页
    case '2': viewBooks(); break;//查看书目
    case '3': borrowBooks(); break;//借阅图书
    case '4': returnBooks(); break;//归还图书
    case '5': logIn(); break;//登录注册页
    case '6': passWord(); break;//管理员登陆，密码页
    case '7': closeApplication(); break;
    default: {
        wrongEnter(23);
        userMainMenu();
    }
    }
}//用户菜单页
void adminiMainMenu(void) {
    sysFlag = 1;//标记为管理端
    loadingAnim();//加载页面
    system("cls");//清屏
    gotoxy(20, 3); printf(":: LIBRARY MANAGEMENT BACKSTAGE SYSTEM ::");
    gotoxy(25, 5); printf("1==> Search Books");
    gotoxy(25, 7); printf("2==> View Books List");
    gotoxy(25, 9); printf("3==> Add Books");
    gotoxy(25, 11); printf("4==> Edit Books");
    gotoxy(25, 13); printf("5==> Delete Books");
    gotoxy(25, 15); printf("6==> View Users List");
    gotoxy(25, 17); printf("7==> User System");
    gotoxy(25, 19); printf("8==> Close the Application");
    gotoxy(20, 21); printf(":::::::::::::::::::::::::::::::::::::::::");//菜单栏
    gotoxy(20, 23); printf("Enter your choice:");
    switch (getch()) {
    case '1': searchBooks(); break;//搜索图书
    case '2': viewBooks(); break;//查看书目
    case '3': addBooks(); break;//添加图书
    case '4': editBooks(); break;//编辑图书
    case '5': deleteBooks(); break;
    case '6': viewUsers(); break;//查看用户列表
    case '7': logIn(); break;//登陆注册页
    case '8': closeApplication(); break;
    default: wrongEnter(25);
        adminiMainMenu();
    }
} //管理员菜单页
void addBooks(void) {
    loadingAnim();
    system("cls");
    int i;
    gotoxy(20, 3); printf(":::::::::::: SELECT CATEGOIES :::::::::::");
    gotoxy(25, 5); printf("1=> Computer");
    gotoxy(25, 7); printf("2=> Electronics");
    gotoxy(25, 9); printf("3=> Electrical");
    gotoxy(25, 11); printf("4=> Civil");
    gotoxy(25, 13); printf("5=> Mechanical");
    gotoxy(25, 15); printf("6=> Architecture");
    gotoxy(25, 17); printf("7=> Art");
    gotoxy(25, 19); printf("8=> Others");
    gotoxy(25, 21); printf("9=> Back to main menu");
    gotoxy(20, 23); printf(":::::::::::::::::::::::::::::::::::::::::");
    gotoxy(20, 25); printf("Enter your choice:");
    scanf("%d", &i);
    if (!(i > 0 && i <= 9)) {
        wrongEnter(31);
    }
    if (i == 9) {
        adminiMainMenu();
    }
    system("cls");
    strcpy(book.catag, catagories[i - 1]);
    fp = fopen("lib.dat", "ab+");
    if (getdata(i) == 1) {//成功输入数据
        fseek(fp, 0, SEEK_END);//文件末尾追加图书数据
        fwrite(&book, sizeof(book), 1, fp);
        fclose(fp);
        gotoxy(20, 14); printf("The Record Is Sucessfully Saved");
        gotoxy(20, 15); printf("Do you want to save more?(Y / N):");
        if (getch() == 'n' || getch() == 'N') {//结束增加图书
            adminiMainMenu();
        }
        else {
            addBooks();
        }//输入数据错误
    }
}//增加图书
int getdata(int i) {
    int t;
    gotoxy(20, 3); printf("Enter the Information Below");
    gotoxy(20, 4); printf(":::::::::::::::::::::::::::::::::::::::::");
    gotoxy(20, 5); printf("::"); gotoxy(59, 5); printf("::");
    gotoxy(20, 6); printf("::"); gotoxy(59, 6); printf("::");
    gotoxy(20, 7); printf("::"); gotoxy(59, 7); printf("::");
    gotoxy(20, 8); printf("::"); gotoxy(59, 8); printf("::");
    gotoxy(20, 9); printf("::"); gotoxy(59, 9); printf("::");
    gotoxy(20, 10); printf(":::::::::::::::::::::::::::::::::::::::::");
    gotoxy(25, 5); printf("Category:");
    gotoxy(36, 5); printf("%s", book.catag);
    gotoxy(25, 6); printf("Book ID:");
    gotoxy(36, 6); scanf("%d", &t);//打印输入界面
    if (checkid(t) == 0) {//ID有重复
        gotoxy(22, 13); printf("\aThe book id already existed\a");
        getch(); adminiMainMenu();
        return 0;
    }
    book.bookID = t;
    gotoxy(25, 7); printf("Book Name:");
    gotoxy(38, 7); scanf("%s", book.bookName);
    gotoxy(25, 8); printf("Author:");
    gotoxy(38, 8); scanf("%s", book.authorName);
    gotoxy(25, 9); printf("Quantity:");
    gotoxy(38, 9); scanf("%d", &book.quantity);
    strcpy(book.catag, catagories[i - 1]);
    return 1;
}
int checkid(int t) {
    rewind(fp);//从文件头开始搜索
    while (fread(&book, sizeof(book), 1, fp) == 1) {
        if (book.bookID == t)
            return 0; //返回0表示存在
    }
    return 1; //返回1表示不存在
} //检查图书序列号是否存在
void searchBooks() {
    loadingAnim(); system("cls");
    if (sysFlag == 0) {
        gotoxy(1, 1); printf("HELLO %s", user.unserName);
    }
    gotoxy(20, 2); printf("::::::::::::: Search Books ::::::::::::");
    gotoxy(25, 4); printf("1=> Search By ID");
    gotoxy(25, 6); printf("2=> Search By Name");
    gotoxy(25, 9); printf("Enter Your Choice");
    fp = fopen("lib.dat", "rb+"); //打开文件，只读模式
    rewind(fp);//从头开始读取文件数据
    switch (getch()) {//选择查询模式
    case '1': searchBookID(); break;
    case '2': searchBookName(); break;
    default:
        wrongEnter(11);
        searchBooks();
    }
    fclose(fp);
}
void searchBookID() {
    int id;
    int findbook = -1;//result of searching
    char search[] = "Searching.....";
    system("cls");
    gotoxy(25, 4); printf("::::Search Books By Id::::");
    gotoxy(25, 6); printf("Enter the book id:");
    scanf("%d", &id);
    gotoxy(25, 8);
    for (int i = 0; i <= strlen(search); i++) {
        printf("%c", search[i]);
        Sleep(100);
    }
    while (fread(&book, sizeof(book), 1, fp) == 1) {
        if (book.bookID == id) {//找到对应图书
            Sleep(2);
            gotoxy(25, 7); printf("The Book Is Available");
            gotoxy(25, 8); printf("::::::::::::::::::::::::::::");
            gotoxy(25, 9); printf(": Catagory:   %s", book.catag);
            gotoxy(52, 9); printf(":");
            gotoxy(25, 10); printf(": ID:         %d", book.bookID);
            gotoxy(52, 10); printf(":");
            gotoxy(25, 11); printf(": Name:       %s", book.bookName);
            gotoxy(52, 11); printf(":");
            gotoxy(25, 12); printf(": Author:     %s", book.authorName);
            gotoxy(52, 12); printf(":");
            gotoxy(25, 13); printf(": Quantity:   %d", book.quantity);
            gotoxy(52, 13); printf(":");
            gotoxy(25, 14); printf("::::::::::::::::::::::::::::");
            findbook = 1;
        }
    }
    if (findbook != 1) {//没有找到对应图书
        gotoxy(25, 8); printf(":::::::::::::::::::");
        gotoxy(25, 9); printf(":");
        gotoxy(43, 9); printf(":");
        gotoxy(25, 10); printf(":::::::::::::::::::");
        gotoxy(27, 9); printf("\aNo Record Found");
    }
    gotoxy(25, 17);
    printf("Try another search?(Y/N)");
    if (getch() == 'y' || getch() == 'Y')
        searchBooks();
    else {
        if (sysFlag == 0) {
            userMainMenu();
        }
        else if (sysFlag == 1) {
            adminiMainMenu();
        }
    }
}
void searchBookName() {
    int findbook = -1;//result of searching
    char search[] = "Searching.....";
    char s[15];
    system("cls");
    gotoxy(20, 4);
    printf("::::::::: Search Books By Name :::::::::");
    gotoxy(20, 6);
    printf("Enter Book Name:");
    scanf("%s", s);
    gotoxy(20, 8);
    for (int i = 0; i <= strlen(search); i++) {
        printf("%c", search[i]);
        Sleep(100);
    }
    while (fread(&book, sizeof(book), 1, fp) == 1) {
        if (strcmp(book.bookName, (s)) == 0) {
            Sleep(2);
            gotoxy(20, 7); printf("The Book Is Available");
            gotoxy(20, 8); printf(":::::::::::::::::::::::::::::::");
            gotoxy(20, 9); printf(": Catagory: %s", book.catag);
            gotoxy(50, 9); printf(":");
            gotoxy(20, 10); printf(": ID:       %d", book.bookID);
            gotoxy(50, 10); printf(":");
            gotoxy(20, 11); printf(": Name:     %s", book.bookName);
            gotoxy(50, 11); printf(":");
            gotoxy(20, 12); printf(": Author:   %s", book.authorName);
            gotoxy(50, 12); printf(":");
            gotoxy(20, 13); printf(": Qantity:  %d", book.quantity);
            gotoxy(50, 13); printf(":");
            gotoxy(20, 14); printf(":::::::::::::::::::::::::::::::");
            findbook = 1;
        }
    }
    if (findbook != 1) {
        gotoxy(20, 8); printf(":::::::::::::::::::");
        gotoxy(20, 9); printf(":");
        gotoxy(38, 9); printf(":");
        gotoxy(20, 10); printf(":::::::::::::::::::");
        gotoxy(22, 9); printf("\aNo Record Found");
    }
    gotoxy(20, 17); printf("Try another search?(Y/N)");
    if (getch() == 'y' || getch() == 'Y') {
        searchBooks();
    }
    else {
        if (sysFlag == 0) {
            userMainMenu();
        }
        else if (sysFlag == 1) {
            adminiMainMenu();
        }
    }
}
void viewBooks(void) { //显示所有书目
    int i = 0, j = 5;
    system("cls");
    if (sysFlag == 0) {
        gotoxy(1, 1); printf("HELLO %s", user.unserName);
    }
    gotoxy(2, 2); printf("::::::::::::::::::::::::::::::Book List:::::::::::::::::::::::::::::::");
    gotoxy(3, 3); printf(" CATEGORY         ID             BOOK NAME      AUTHOR       QUANTITY");
    fp = fopen("lib.dat", "rb");
    while (fread(&book, sizeof(book), 1, fp) == 1) {
        gotoxy(4, j); printf("%s", book.catag);
        gotoxy(20, j); printf("%d", book.bookID);
        gotoxy(37, j); printf("%s", book.bookName);
        gotoxy(51, j); printf("%s", book.authorName);
        gotoxy(66, j); printf("%d", book.quantity);
        printf("\n\n");
        j++; //next row
        i += book.quantity;//sum of book
    }
    gotoxy(3, 25); printf("Total Books =%d", i);
    fclose(fp);
    gotoxy(35, 25); returnfunc();
}
void editBooks(void) {
    loadingAnim(); system("cls");
    int c = 0, d;
    gotoxy(20, 4); printf("::::::::: Edit Books Section ::::::::::");
    char another = 'y';
    while (another == 'y') {
        gotoxy(21, 6); printf("Enter Book ID to be edited:");
        scanf("%d", &d);
        fp = fopen("lib.dat", "rb+");
        while (fread(&book, sizeof(book), 1, fp) == 1) {
            if (checkid(d) == 0) {
                gotoxy(21, 7); printf("The Book Is Available");
                gotoxy(21, 8); printf("The Book Category:%s", book.catag);
                gotoxy(21, 9); printf("The Book ID:%d", book.bookID);
                gotoxy(21, 10); printf("Enter New Name:"); scanf("%s", book.bookName);
                gotoxy(21, 11); printf("Enter New Author:"); scanf("%s", book.authorName);
                gotoxy(21, 12); printf("Add New Quantity:"); scanf("%d", &book.quantity);
                fseek(fp, ftell(fp) - sizeof(book), 0);
                fwrite(&book, sizeof(book), 1, fp);
                fclose(fp);
                Sleep(10);
                gotoxy(21, 14); printf("The record is modified");
                c = 1;
            }
            if (c == 0) {
                gotoxy(21, 9); printf("No record found");
            }
        }
        gotoxy(21, 16); printf("Modify Another Record?(Y/N)");
        fflush(stdin);
        another = getch();
    }
    returnfunc();
}
void deleteBooks() {
    loadingAnim();
    system("cls");
    int d, findbook = -1;
    char another = 'y';
    while (another == 'y') {
        system("cls");
        gotoxy(10, 5);
        printf("Enter the Book ID to delete:");
        scanf("%d", &d);
        fp = fopen("lib.dat", "rb+");
        rewind(fp);
        while (fread(&book, sizeof(book), 1, fp) == 1) {
            if (book.bookID == d) {
                gotoxy(10, 7);
                printf("The Book Record Is Available");
                gotoxy(10, 8);
                printf("Book name is %s", book.bookName);
                findbook = 1;
            }
        }
        if (findbook != 1) {
            gotoxy(10, 10);
            printf("No record is found modify the search");
            if (getch()) {
                gotoxy(15, 10);
                returnfunc();
                adminiMainMenu();
            }
        }
        if (findbook == 1) {
            gotoxy(10, 9);
            printf("Do you want to delete it?(Y/N):");
            if (getch() == 'y') {
                ft = fopen("test.dat", "wb+");  //temporary file for delete
                rewind(fp);
                while (fread(&book, sizeof(book), 1, fp) == 1) {
                    if (book.bookID != d) {
                        fseek(ft, 0, SEEK_CUR);
                        fwrite(&book, sizeof(book), 1, ft);
                    } //write all in tempory file except that we want to delete
                }
                fclose(ft);
                fclose(fp);
                remove("lib.dat");//delete lib
                rename("test.dat", "lib.dat");
                fp = fopen("lib.dat", "rb+");
                gotoxy(10, 10);
                printf("The Record Is Sucessfully Deleted");
                findbook = -1;
                gotoxy(10, 11);
                printf("Delete another record?(Y/N)");

            }
            else {
                adminiMainMenu();
            }
            fflush(stdin);
            another = getch();
        }
    }
    gotoxy(10, 15);
    adminiMainMenu();
}
void borrowBooks() {
    int n;
    loadingAnim(); system("cls");
    gotoxy(20, 4); printf("::::::::::: BOOK BORROWING ::::::::::::");
    gotoxy(20, 5); printf("Welcome %s!", user.unserName);
    gotoxy(20, 6); printf("Please enter the book ID to borrow:");
    scanf("%d", &n);
    getchar();
    gotoxy(21, 7); printf("The book status:");
    int existLabel = searchID(n);
    if (existLabel == 1) {
        gotoxy(21, 8); printf("Not included in the library.");
        gotoxy(21, 9); printf("Want to borrow other books? (Y/N):");
        switch (getchar()) {
        case'y': borrowBooks(); break;
        case 'Y': borrowBooks(); break;
        case 'N': userMainMenu(); break;
        case 'n': userMainMenu(); break;
        }
    }
    else if (existLabel == 0) {
        if (book.quantity == 0) {
            gotoxy(21, 8); printf("There are no books left in the library.");
            gotoxy(21, 9); printf("Want to borrow other books? (Y/N):");
            switch (getchar()) {
            case 'y': borrowBooks(); break;
            case 'Y': borrowBooks(); break;
            case 'N': userMainMenu(); break;
            case 'n': userMainMenu(); break;
            }
        }
        else {
            gotoxy(21, 8); printf("The book is available!");
            gotoxy(21, 9); printf("Confirm to rent? (Y/N):");
        a:          switch (getchar()) {
        case'y': gotoxy(21, 10); printf("Book rental success!");
            changeNum(-1);//qty减少函数
            break;
        case 'Y':
            gotoxy(21, 11); printf("Book rental success!");
            changeNum(-1);//qty减少函数
            break;
        case 'N': break;
        case 'n': break;
        default: goto a;
        }
        }getchar();
        gotoxy(21, 12); printf("Want to borrow other books? (Y/N):");
        switch (getchar()) {
        case 'y': borrowBooks(); break;
        case 'Y': borrowBooks(); break;
        case 'N': userMainMenu(); break;
        case 'n': userMainMenu(); break;
        }
    }
}
void returnBooks() {
    int n; char answer;
    loadingAnim(); system("cls");
    if (user.borrowedBookNum == 0) {
        gotoxy(20, 4); printf("::::::::::: BOOK RETURNING ::::::::::::");
        gotoxy(20, 6); printf("You have not borrowed any books.");
        getchar();
        userMainMenu();
    }
    gotoxy(20, 4); printf("::::::::::: BOOK RETURNING ::::::::::::");
    gotoxy(20, 5); printf("Hello %s!", user.unserName);
    gotoxy(20, 6); printf("Please enter the book ID to return:");
    scanf(" %d", &n); getchar();
    int existLabel = searchID(n);
    if (existLabel == 1) {
        gotoxy(21, 8); printf("The book does not belong to the library.");
        gotoxy(21, 9); printf("Want to return other books? (Y/N):");
        switch (getchar()) {
        case'y': returnBooks(); break;
        case 'Y': returnBooks(); break;
        case 'N': userMainMenu(); break;
        case 'n': userMainMenu(); break;
        }
    }
    if (existLabel == 0) {
        gotoxy(21, 8); printf("The book information was found.");
        gotoxy(21, 9); printf("Confirm to return? (Y/N):");
        switch (getchar()) {
        case'y': gotoxy(21, 11); printf("Successfully returned!");
            changeNum(1);//qty增加函数
            break;
        case 'Y':
            gotoxy(21, 11); printf("Successfully returned!");
            changeNum(1);//qty增加函数
            break;
        case 'N': break;
        case 'n': break;
        default: break;
        }
        getchar();
        gotoxy(21, 12); printf("Want to return other books? (Y/N):");
        switch (getchar()) {
        case 'y': returnBooks(); break;
        case 'Y': returnBooks(); break;
        case 'N': userMainMenu(); break;
        case 'n': userMainMenu(); break;
        default: userMainMenu();
        }
    }
}
int searchID(int t) {
    fp = fopen("lib.dat", "rb+"); rewind(fp);//从文件头开始搜索
    while (fread(&book, sizeof(book), 1, fp) == 1) {
        if (book.bookID == t)
            return 0; //返回0表示存在
    }
    return 1; //返回1表示不存在
} //检查图书序列号是否存在
void changeNum(int num) {
    bookTrans = book;
    bookTrans.quantity += num;
    fp = fopen("lib.dat", "rb+");
    while (fread(&book, sizeof(book), 1, fp) == 1) {
        if (checkid(bookTrans.bookID) == 0) {
            fseek(fp, ftell(fp) - sizeof(bookTrans), 0);
            fwrite(&bookTrans, sizeof(bookTrans), 1, fp);
            fclose(fp);
        }
    }
    userTrans = user;
    userTrans.borrowedBookNum -= num;
    fu = fopen("account.dat", "rb+");
    rewind(fu);//从文件头开始搜索
    while (fread(&user, sizeof(user), 1, fu) == 1) {
        if (strcmp(user.id, userTrans.id) == 0) {
            fseek(fu, ftell(fu) - sizeof(userTrans), 0);
            fwrite(&userTrans, sizeof(userTrans), 1, fu);
            fclose(fu);
        }
    }
}
void returnfunc(void) {
    printf("   Press ENTER to return to main menu");
a:
    if (getch() == 13) { //ENTER键返回
        if (sysFlag == 0) {
            userMainMenu();
        }
        else if (sysFlag == 1) {
            adminiMainMenu();
        }
    }
    else
        goto a;
}
void closeApplication(void) {
    system("cls");
    gotoxy(20, 3); printf("\tLibrary Management System");
    gotoxy(20, 5); printf("\tMini Application in C Language");
    gotoxy(20, 7); printf("\tit is produced by");
    gotoxy(20, 9); printf("\t ECUSTer-2020");
    gotoxy(20, 11); printf(":::::::::::::::::::::::::::::::::::::::");
    gotoxy(20, 13); printf(":::::::::::::::::::::::::::::::::::::::");
    gotoxy(20, 15); printf("Exiting in 3 second...........>");
    Sleep(3000); exit(0);
}
void wrongEnter(int i) {
    gotoxy(10, i); printf("\aWrong Entry!!Please re-entered correct option");
    getchar();
}
void logIn() {
    loadingAnim();//加载页面
a:  system("cls");//清屏
    gotoxy(20, 3); printf(":::::::::: USER LOGIN SYSTEM ::::::::::");
    gotoxy(22, 5); printf("PLEASE CHOOSE TO:");
    gotoxy(22, 8); printf("1==> I already had an account.");
    gotoxy(22, 10); printf("2==> I want to registor a new account.");
    gotoxy(22, 12); printf("3==> Administrator Login");
    gotoxy(20, 14); printf(":::::::::::::::::::::::::::::::::::::::::");//菜单栏
    gotoxy(20, 16); printf("Enter your choice:");
    switch (getch()) {
    case'1':signIn(); break;
    case'2':signUp(); break;
    case'3':passWord(); break;
    default:wrongEnter(18); goto a;
    }
}
void signUp() {
    char pass1[100], pass2[100], ch = '\0';
    int i = 0, j = 0;
    loadingAnim();//加载页面
a:  system("cls");//清屏
    gotoxy(20, 3); printf(":::::::::: REGISTOR ACCOUNT ::::::::::");
    gotoxy(20, 5); printf("PLEASE ENTER THE PERSONAL INFORMATION:");
    gotoxy(22, 7); printf("UERNAME: ");
    gotoxy(22, 9); printf("STUDENT ID: ");
    gotoxy(22, 11); printf("PASSWORD: ");
    gotoxy(22, 13); printf("PASSWORD AGAIN: ");
    gotoxy(20, 15); printf(":::::::::::::::::::::::::::::::::::::::");//菜单栏
    gotoxy(31, 7); scanf("%s", user.unserName);
    gotoxy(34, 9); scanf("%s", &user.id);
    gotoxy(32, 11);
    while (ch != 13) {
        ch = getch();
        if (ch >= 32 && ch <= 126) {
            putch('*');
            pass1[i] = ch;
            i++;
        }
    }//输入密码，存储
    pass1[i] = '\0';
    ch = '\0';
    gotoxy(38, 13);
    while (ch != 13) {
        ch = getch();
        if (ch >= 32 && ch <= 126) {
            putch('*');
            pass2[j] = ch;
            j++;
        }
    }//再次输入密码，存储
    pass2[j] = '\0';
    if (strcmp(pass1, pass2) == 0) {//密码比对
        strcpy(user.pwd, pass2);
        user.borrowedBookNum = 0;
        fu = fopen("account.dat", "ab+");
        fseek(fu, 0, SEEK_END);//文件末尾追加用户
        fwrite(&user, sizeof(user), 1, fu);
        fclose(fu);
        gotoxy(22, 18); printf("REGISTOR SUCCESSFULLY");
        getchar(); getchar();
        signIn();
    }
    else {
        gotoxy(22, 14); printf("INCONSISTENT PASSWORDS!!!");
        getchar(); getchar(); goto a;
    }
}
void signIn() {
    loadingAnim();//加载页面
a:  system("cls");//清屏
    int verNum, finduser = 0, i = 0, verti;
    char name[100], passInput[100], ch = '\0';
    srand((unsigned)time(NULL));
    verNum = ((rand() * rand()) % 9000) + 1000;//生成四位数验证码
    gotoxy(20, 3); printf(":::::::::::: LOGIN SYSTEM :::::::::::::");
    gotoxy(22, 7); printf("USERNAME/STUDENT ID: ");
    gotoxy(22, 11); printf("PASSWORD: ");
    gotoxy(22, 14); printf("VERIFICATION CODE: ");
    gotoxy(50, 14); printf("%4d", verNum);
    gotoxy(20, 15); printf(":::::::::::::::::::::::::::::::::::::::");//菜单栏
    gotoxy(44, 7); scanf("%s", name);
    fu = fopen("account.dat", "rb+");
    fseek(fu, 0, SEEK_SET);//从头搜索用户
    while (fread(&user, sizeof(user), 1, fu) == 1) {//搜索账号
        if (strcmp(user.id, name) == 0 || strcmp(user.unserName, name) == 0) {
            finduser = 1;
            break;
        }
    }
    if (finduser != 1) {//无该账号
        gotoxy(20, 18); printf("Account Does Not Exist");
        getchar();
        goto a;
    }
    gotoxy(36, 11);
    while (ch != 13) {
        ch = getch();
        if (ch >= 32 && ch <= 126) {
            putch('*');
            passInput[i] = ch;
            i++;
        }
    }//输入密码，存储
    passInput[i] = '\0';
    gotoxy(42, 14); scanf("%d", &verti);
    if (verti == verNum) {
        if (strcmp(passInput, user.pwd) == 0) {//密码正确
            gotoxy(20, 18); printf("Login Successfully!");
            gotoxy(20, 20); printf("WELCOME %s!", user.unserName);
            getchar(); getchar();
            userMainMenu();
        }
        else {
            gotoxy(20, 18); printf("Incorrect Password!");
            getchar(); getchar();
            goto a;
        }
    }
    else {
        gotoxy(20, 18); printf("Incorrect Verification Code!");
        getchar(); getchar();
        goto a;
    }
}
void viewUsers(void) { //显示全部用户
    int i = 0, j = 4;
    system("cls");
    gotoxy(1, 1); printf("::::::::::::::::::::::::::::: USER LIST ::::::::::::::::::::::::::::::");
    gotoxy(1, 2); printf(" USER ID      USERNAME              PASSWORD                 Borrowed");
    fu = fopen("account.dat", "rb");
    while (fread(&user, sizeof(user), 1, fu) == 1) {
        gotoxy(2, j); printf("%s", user.id);
        gotoxy(15, j); printf("%s", user.unserName);
        gotoxy(37, j); printf("%s", user.pwd);
        gotoxy(65, j); printf("%d", user.borrowedBookNum);
        printf("\n\n"); i++; j++;
    }
    gotoxy(3, 25); printf("Total Users =%d", i);
    fclose(fu); gotoxy(35, 25); returnfunc();
}
//程序结束