#define _CRT_SECURE_NO_WARNINGS//����vs���������
#include<conio.h>
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
void closeApplication(void);//finished
void deleteBooks(void);//finished
void editBooks(void);//finished
void loadingAnim(void);//finished
void passWord(void);//finished
void previewPage(void);//finished
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
#define N 1000000
int flag = -1;
char catagories[N][15] = { "Computer","Electronics","Electrical","Civil","Mechanical","Architecture" };
char passwordUser[20] = { "000000" };
char passwordAdmini[20] = { "123456" };
struct books {
    char catag[15];//ͼ�����ĵ�ַ
    int bookID;//ͼ����
    char bookName[20];//ͼ����
    char authorName[20];//������
    int quantity;//����
}book;
FILE* fp, * ft, * fs;
COORD coord = { 0, 0 };
void gotoxy(int x, int y) {
    coord.X = x;
    coord.Y = y; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}//print�ĳ�ʼλ������
int main(void) {
    previewPage();
    getchar();
    return 0;
}//���������������ü�ª��
void previewPage(void) {
    system("cls");//����
    char start[] = "Welcome for Using ECUST Library Management System";
    gotoxy(10, 10);
    for (int i = 0; i < 15; i++) {
        Sleep(50); printf(":");
    }
    for (int i = 0; i <= strlen(start); i++) {
        Sleep(50); printf("%c", start[i]);
    }
    for (int i = 0; i < 15; i++) {
        Sleep(50); printf(":");
    }//�����ӭ��
    Sleep(1000);
    passWord();//����ϵͳ�������
}
void loadingAnim() {
    for (int i = 0; i < 1; i++) {
        system("cls"); gotoxy(20, 10);
        char w[] = "LOADING........";
        for (int loader = 0; loader < 10; loader++) {
            Sleep(100); printf("%c", w[loader]);
        }//���ֹ���
        Sleep(50);
    }
}//����ҳ��
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
    }//�������
    gotoxy(15, 7); printf("Enter Password:");//�����ʾ��
    while (ch != 13) {
        ch = getch();
        if (ch >= 32 && ch <= 126) {
            putch('*');
            pass[i] = ch;
            i++;
        }
    }//�������룬�洢
    pass[i] = '\0';
    if (strcmp(pass, passwordUser) == 0) {//����ȶԣ��û���
        gotoxy(15, 9); printf("Now You Are Logged In!");
        gotoxy(17, 10); printf("===>Press any key to countinue...");
        getch(); userMainMenu();//�����û��ˣ������˴��������û��˵�¼ע��ҳ
    }//�û�ϵͳ
    else if (strcmp(pass, passwordAdmini) == 0) {//����ȶԣ������
        gotoxy(15, 9); printf("Now You Are Logged In (Administration Mode)!");
        gotoxy(17, 10); printf("\n===>Press any key to countinue...");
        getch(); adminiMainMenu();
    }//����Աϵͳ
    else {
        gotoxy(15, 16); printf("\aWarning!!! Incorrect Password!");
        getch(); passWord();//��������
    }//�������
}//��½����
void userMainMenu(void) {
    flag = 0;//���Ϊ�û���
    loadingAnim();//����ҳ��
    system("cls");//����
    gotoxy(20, 3); printf("::::::: LIBRARY MANAGEMENT SYSTEM :::::::");
    gotoxy(25, 5); printf("1==> Search Books");
    gotoxy(25, 7); printf("2==> View Books List");
    gotoxy(25, 9); printf("3==> Borrow Books");
    gotoxy(25, 11); printf("4==> Return Books");
    gotoxy(25, 13); printf("5==> Log Out");
    gotoxy(25, 15); printf("6==> Administrator Login");
    gotoxy(20, 17); printf(":::::::::::::::::::::::::::::::::::::::::");//�˵���
    gotoxy(20, 19); printf("Enter your choice:");
    switch (getch()) {
    case '1': searchBooks(); break;//����ͼ��ҳ
    case '2': viewBooks(); break;//�鿴��Ŀ
    case '3': borrowBooks(); break;//����ͼ��
    case '4': returnBooks(); break;//�黹ͼ��
    case '5': passWord(); break;//�˳���¼�������˴��������¼ע��ҳ
    case '6': passWord(); break;//����Ա��½������ҳ
    default: {
        wrongEnter(23);
        if (getch()) {
            userMainMenu();
        }
    }
    }
}//�û��˵�ҳ
void adminiMainMenu(void) {
    flag = 1;//���Ϊ�����
    loadingAnim();//����ҳ��
    system("cls");//����
    gotoxy(20, 3); printf(":: LIBRARY MANAGEMENT BACKSTAGE SYSTEM ::");
    gotoxy(25, 5); printf("1==> Search Books");
    gotoxy(25, 7); printf("2==> View Books List");
    gotoxy(25, 9); printf("3==> Add Books");
    gotoxy(25, 11); printf("4==> Edit Books");
    gotoxy(25, 13); printf("5==> Delete Books");
    gotoxy(25, 15); printf("6==> Search User");
    gotoxy(25, 17); printf("7==> View Users List");
    gotoxy(25, 19); printf("8==> User System");
    gotoxy(25, 21); printf("9==> Close the Application");
    gotoxy(20, 23); printf(":::::::::::::::::::::::::::::::::::::::::");//�˵���
    gotoxy(20, 25); printf("Enter your choice:");
    switch (getch()) {
    case '1': searchBooks(); break;//����ͼ��
    case '2': viewBooks(); break;//�鿴��Ŀ
    case '3': addBooks(); break;//���ͼ��
    case '4': editBooks(); break;//�༭ͼ��
    case '5': deleteBooks(); break;
    case '6': break;//�����û�
    case '7': break;//�鿴�û��б�
    case '8': userMainMenu(); break;//�û��ˣ������������½ע��ҳ
    case '9': closeApplication(); break;
    default: wrongEnter(25);
        if (getch()){
            adminiMainMenu();
    }
    }
} //����Ա�˵�ҳ
void addBooks(void) {
    loadingAnim(); system("cls");
    int i;
    gotoxy(20, 3); printf(":::::::::::: SELECT CATEGOIES :::::::::::");
    gotoxy(25, 5); printf("1=> Computer");
    gotoxy(25, 7); printf("2=> Electronics");
    gotoxy(25, 9); printf("3=> Electrical");
    gotoxy(25, 11); printf("4=> Civil");
    gotoxy(25, 13); printf("5=> Mechanical");
    gotoxy(25, 15); printf("6=> Architecture");
    gotoxy(25, 17); printf("7=> Back to main menu");
    gotoxy(20, 19); printf(":::::::::::::::::::::::::::::::::::::::::");
    gotoxy(20, 21); printf("Enter your choice:");
    scanf("%d", &i);
    if (!(i > 0 && i <= 7)) {
        wrongEnter(25);
    }
    if (i = 7) adminiMainMenu(); {
        system("cls");
    }
    strcpy(book.catag, catagories[i - 1]);
    fp = fopen("lib.dat", "ab+");
    if (getdata(i) == 1) {//�ɹ���������
        fseek(fp, 0, SEEK_END);//�ļ�ĩβ׷��ͼ������
        fwrite(&book, sizeof(book), 1, fp); fclose(fp);
        gotoxy(20, 14); printf("The Record Is Sucessfully Saved");
        gotoxy(20, 15); printf("Do you want to save more?(Y / N):");
        if (getch() == 'n' || getch() == 'N')//��������ͼ��
            adminiMainMenu();
        else
            system("cls");
        addBooks();
    }
    else addBooks();//�������ݴ���
}//����ͼ��
int getdata(int i) {
    int t;
    gotoxy(20, 3); printf("Enter the Information Below");
    gotoxy(20, 4); printf(":::::::::::::::::::::::::::::::::::::::::");
    gotoxy(20, 5); printf("::"); gotoxy(61, 5); printf("::");
    gotoxy(20, 6); printf("::"); gotoxy(61, 6); printf("::");
    gotoxy(20, 7); printf("::"); gotoxy(61, 7); printf("::");
    gotoxy(20, 8); printf("::"); gotoxy(61, 8); printf("::");
    gotoxy(20, 9); printf("::"); gotoxy(61, 9); printf("::");
    gotoxy(20, 10); printf(":::::::::::::::::::::::::::::::::::::::::");
    gotoxy(22, 5); printf("Category:");
    gotoxy(33, 5); printf("%s", book.catag);
    gotoxy(22, 6); printf("Book ID:\t");
    gotoxy(33, 6); scanf("%d", &t);//��ӡ�������
    if (checkid(t) == 0) {//IDû���ظ�
        gotoxy(22, 13); printf("\aThe book id already existed\a");
        getch(); adminiMainMenu();
        return 0;
    }
    book.bookID = t;
    gotoxy(22, 7); printf("Book Name:");
    gotoxy(33, 7); scanf("%s", book.bookName);
    gotoxy(22, 8); printf("Author:");
    gotoxy(33, 8); scanf("%s", book.authorName);
    gotoxy(22, 9); printf("Quantity:");
    gotoxy(33, 9); scanf("%d", &book.quantity);
    return 1;
}
int checkid(int t) {
    rewind(fp);//���ļ�ͷ��ʼ����
    while (fread(&book, sizeof(book), 1, fp) == 1) {
        if (book.bookID == t)
            return 0; //����0��ʾ����
    }
    return 1; //����1��ʾ������
} //���ͼ�����к��Ƿ����
void searchBooks() {
    loadingAnim(); system("cls");
    printf("::::::::::::::::::::::::::::: Search Books :::::::::::::::::::::::::::::");
    gotoxy(25, 3); printf("1=> Search By ID");
    gotoxy(25, 5); printf("2=> Search By Name");
    gotoxy(25, 9); printf("Enter Your Choice");
    fp = fopen("lib.dat", "rb+"); //���ļ���ֻ��ģʽ
    rewind(fp);//��ͷ��ʼ��ȡ�ļ�����
    switch (getch()) {//ѡ���ѯģʽ
    case '1': searchBookID(); break;
    case '2': searchBookName(); break;
    default: wrongEnter(11); searchBooks();
    }
    fclose(fp);
}
void searchBookID() {
    int id; int findbook=0;
    char search[] = "Searching....."; system("cls");
    gotoxy(25, 4); printf("::::Search Books By Id::::");
    gotoxy(25, 6); printf("Enter the book id:");
    scanf("%d", &id);
    gotoxy(25, 8);
    for (int i = 0; i <= strlen(search); i++) {
        printf("%c", search[i]); Sleep(100);
    }
    while (fread(&book, sizeof(book), 1, fp) == 1) {
        if (book.bookID == id) {//�ҵ���Ӧͼ��
            Sleep(2);
            gotoxy(25, 7); printf("The Book Is Available");
            gotoxy(25, 8); printf("::::::::::::::::::::::::::::");
            gotoxy(25, 9); printf(": Catagory:%s", book.catag);
            gotoxy(47, 9); printf(":");
            gotoxy(25, 10); printf(": ID:%d", book.bookID);
            gotoxy(47, 10); printf(":");
            gotoxy(25, 11); printf(": Name:%s", book.bookName);
            gotoxy(47, 11); printf(":");
            gotoxy(25, 12); printf(": Author:%s ", book.authorName);
            gotoxy(47, 12); printf(":");
            gotoxy(25, 13); printf(": Quantity:%d ", book.quantity);
            gotoxy(47, 13); printf(":");
            gotoxy(25, 14); printf("::::::::::::::::::::::::::::");
            findbook = 1;
        }
    }
    if (findbook != 1) {//û���ҵ���Ӧͼ��
        gotoxy(20, 8); printf(":::::::::::::::::::");
        gotoxy(20, 9); printf(":");
        gotoxy(38, 9); printf(":");
        gotoxy(20, 10); printf(":::::::::::::::::::");
        gotoxy(22, 9); printf("\aNo Record Found");
    }
    gotoxy(20, 17);
    printf("Try another search?(Y/N)");
    if (getch() == 'y' || getch() == 'Y')
        searchBooks();
    else {
        if (flag == 0) {
            userMainMenu();
        }
        else if (flag == 1) {
            adminiMainMenu();
        }
        else {
            passWord();
        }
    }
}
void searchBookName() {
    int d=0; char s[15];
    system("cls");
    gotoxy(20, 4);
    printf("::::::::: Search Books By Name :::::::::");
    gotoxy(20, 5);
    printf("Enter Book Name:");
    scanf("%s", s);
    while (fread(&book, sizeof(book), 1, fp) == 1) {
        if (strcmp(book.bookName, (s)) == 0) {
            gotoxy(20, 7); printf("The Book Is Available");
            gotoxy(20, 8); printf(":::::::::::::::::::::::::::::::");
            gotoxy(20, 9); printf(": Catagory:%s", book.catag);
            gotoxy(50, 9); printf(":");
            gotoxy(20, 10); printf(": ID:%d", book.bookID);
            gotoxy(50, 10); printf(":");
            gotoxy(20, 11); printf(": Name:%s", book.bookName);
            gotoxy(50, 11); printf(":");
            gotoxy(20, 12); printf(": Author:%s", book.authorName);
            gotoxy(50, 12); printf(":");
            gotoxy(20, 13); printf(": Qantity:%d", book.quantity);
            gotoxy(50, 13); printf(":");
            gotoxy(20, 14); printf(":::::::::::::::::::::::::::::::");
            d++;
        }
    }
    if (d == 0) {
        gotoxy(22, 9); printf("\aNo Record Found");
    }
    gotoxy(20, 17); printf("Try another search?(Y/N)");
    if (getch() == 'y' || getch() == 'Y') {
        searchBooks();
    }
    else {
        if (flag == 0) {
            userMainMenu();
        }
        else if (flag == 1) {
            adminiMainMenu();
        }
        else {
            passWord();
        }
    }
}
void viewBooks(void) { //��ʾ������Ŀ
    int i = 0, j = 4;
    system("cls");
    gotoxy(1, 1); printf("::::::::::::::::::::::::::::::Book List:::::::::::::::::::::::::::::::");
    gotoxy(2, 2); printf(" CATEGORY         ID             BOOK NAME      AUTHOR       QUANTITY");
    fp = fopen("lib.dat", "rb");
    while (fread(&book, sizeof(book), 1, fp) == 1) {
        gotoxy(3, j); printf("%s", book.catag);
        gotoxy(20, j); printf("%d", book.bookID);
        gotoxy(35, j); printf("%s", book.bookName);
        gotoxy(50, j); printf("%s", book.authorName);
        gotoxy(64, j); printf("%d", book.quantity);
        printf("\n\n"); j++; i += book.quantity;
    }
    gotoxy(3, 25); printf("Total Books =%d", i);
    fclose(fp); gotoxy(35, 25); returnfunc();
}
void editBooks(void){
    loadingAnim(); system("cls");
    int c = 0, d;
    gotoxy(20, 4); printf("::::::::: Edit Books Section ::::::::::");
    char another = 'y';
    while (another == 'y') {
        system("cls");
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
                fwrite(&book, sizeof(book), 1, fp); fclose(fp);
                Sleep(10); 
                gotoxy(21, 14); printf("The record is modified");
                c = 1;
            }
            if (c == 0) {
                gotoxy(15, 9); printf("No record found");
            }
        }
        gotoxy(15, 16); printf("Modify Another Record?(Y/N)");
        fflush(stdin); another = getch();
    }
    returnfunc();
}
void deleteBooks(){
    loadingAnim(); system("cls");
    int d; char another = 'y', findbook='\0';
    while (another == 'y') {
        system("cls");
        gotoxy(10, 5); printf("Enter the Book ID to delete:"); scanf("%d", &d);
        fp = fopen("lib.dat", "rb+");
        rewind(fp);
        while (fread(&book, sizeof(book), 1, fp) == 1) {
            if (book.bookID == d){
                gotoxy(10, 7); printf("The Book Record Is Available");
                gotoxy(10, 8); printf("Book name is %s", book.bookName);
                findbook = 't';
            }
        }
        if (findbook != 't') {
            gotoxy(10, 10); printf("No record is found modify the search");
            if (getch()) {
                adminiMainMenu();
            }
        }
        if (findbook == 't') {
            gotoxy(10, 9); printf("Do you want to delete it?(Y/N):");
            if (getch() == 'y') {
                ft = fopen("test.dat", "wb+");  //temporary file for delete
                rewind(fp);
                while (fread(&book, sizeof(book), 1, fp) == 1) {
                    if (book.bookID != d) {
                        fseek(ft, 0, SEEK_CUR);
                        fwrite(&book, sizeof(book), 1, ft); //write all in tempory file except that
                    }
                }
                fclose(ft); fclose(fp);
                remove("lib.dat"); rename("test.dat", "lib.dat"); //copy all item from temporary file to fp except that
                fp = fopen("lib.dat", "rb+");    //we want to delete
                if (findbook == 't') {
                    gotoxy(10, 10); printf("The Record Is Sucessfully Deleted");
                    gotoxy(10, 11); printf("Delete another record?(Y/N)");
                }
            }
            else
                adminiMainMenu();
            fflush(stdin); another = getch();
        }
    }
    gotoxy(10, 15);
    adminiMainMenu();
}
void borrowBooks() {
    int n;
    loadingAnim(); system("cls");
    gotoxy(20, 4); printf("::::::::::: BOOK BORROWING ::::::::::::");
    gotoxy(21, 5); printf("���ã����������������鼮�ţ�"); scanf("%d", &n);
    gotoxy(21, 6); printf("��ǰ���鼮��״̬Ϊ��");
    int existLabel = searchID(n);
    if (existLabel == 1) {
        gotoxy(21, 7); printf("����δ��¼��ͼ�顣");
        gotoxy(21, 8); printf("�Ƿ��ѯ�����鼮��(Y/N):");
        switch (getchar()) {
        case'y': borrowBooks(); break;
        case 'Y': borrowBooks(); break;
        case 'N': userMainMenu(); break;
        case 'n': userMainMenu(); break;
        }
    }
    else if (existLabel == 0) {
        if (book.quantity == 0) {
            gotoxy(21, 7); printf("������ʣ�࣬ͼ������С�");
            gotoxy(21, 8); printf("�Ƿ��ѯ�����鼮��(Y/N):");
            switch (getchar()) {
            case 'y': borrowBooks(); break;
            case 'Y': borrowBooks(); break;
            case 'N': userMainMenu(); break;
            case 'n': userMainMenu(); break;
            }
        }
        else {
            gotoxy(21, 7); printf("ͼ���ڹݣ�����衣");
            gotoxy(21, 8); printf("�Ƿ�ȷ����裿(Y/N):");
a:          switch (getchar()) {
            case'y': gotoxy(21, 10);printf("���ɹ���");
                //qty���ٺ���
                break;
            case 'Y':
                gotoxy(21, 10); printf("���ɹ���");
                //qty���ٺ���
                break;
            case 'N': break;
            case 'n': break;
            default: goto a;
            }
        }
        gotoxy(21, 11); printf("�Ƿ������裿(Y/N):");
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
    gotoxy(20, 4); printf("::::::::::: BOOK RETURNING ::::::::::::");
    printf("���ã���������Ҫ�黹���鼮�ţ�"); scanf("%d", &n);
    int existLabel = searchID(n);
    if (existLabel == 1) {
        gotoxy(21, 7); printf("����δ��¼��ͼ�顣");
        gotoxy(21, 8); printf("�Ƿ��ѯ�����鼮��(Y/N):");
        switch (getchar()) {
        case'y': returnBooks(); break;
        case 'Y': returnBooks(); break;
        case 'N': userMainMenu(); break;
        case 'n': userMainMenu(); break;
        }
    }
    if (existLabel == 0) {
        gotoxy(21, 7); printf("���ҵ���ͼ�顣");
        gotoxy(21, 8); printf("ȷ��Ҫ�黹��(Y/N):");
        switch (getchar()) {
        case'y': gotoxy(21, 10); printf("�黹�ɹ���");
            //qty���Ӻ���
            break;
        case 'Y':
            gotoxy(21, 10); printf("�黹�ɹ���");
            //qty���Ӻ���
            break;
        case 'N': break;
        case 'n': break;
        default: break;
        }
        gotoxy(21, 11); printf("�Ƿ������裿(Y/N):");
        switch (getchar()) {
        case 'y': returnBooks(); break;
        case 'Y': returnBooks(); break;
        case 'N': userMainMenu(); break;
        case 'n': userMainMenu(); break;
        }
    }
}
int searchID(int t) {
    fp = fopen("lib.dat", "rb+"); rewind(fp);//���ļ�ͷ��ʼ����
    while (fread(&book, sizeof(book), 1, fp) == 1) {
        if (book.bookID == t)
            return 0; //����0��ʾ����
    }
    return 1; //����1��ʾ������
} //���ͼ�����к��Ƿ����

void increaseBooks() {
    
}
void decreaseBooks() {

}
 
void returnfunc(void) {
    printf(" Press ENTER to return to main menu");
a:
    if (getch() == 13) { //ENTER������
        if (flag == 0) {
            userMainMenu();
        }
        else if (flag == 1) {
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
    gotoxy(20, 11); printf("::::::::::::::::::::::::::::");
    gotoxy(20, 13); printf("::::::::::::::::::::::::::::");
    gotoxy(20, 15); printf("Exiting in 3 second...........>");
    flushall(); Sleep(3000); exit(0);
}
void wrongEnter(int i) {
    gotoxy(10, i); printf("\aWrong Entry!!Please re-entered correct option");
    getchar();
}
//�������