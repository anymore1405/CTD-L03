//Chương trình Phân tích từ vựng
#include <stdio.h>
#include <curses.h>
#include <ctype.h>
#include <string.h>
#include "slc1.h"

//--Phần khai báo biến và dữ liệu
//Bảng 17 từ khóa và từ tố tương ứng
struct keyword keywtb[] =
        {
                {begin_token,     "BEGIN"},
                {end_token,       "END"},
                {int_token,       "INT"},
                {var_token,       "VAR"},
                {procedure_token, "PROC"},
                {call_token,      "CALL"},
                {read_token,      "READ"},
                {write_token,     "WRITE"},
                {if_token,        "IF"},
                {then_token,      "THEN"},
                {else_token,      "ELSE"},
                {fi_token,        "FI"},
                {while_token,     "WHILE"},
                {do_token,        "DO"},
                {od_token,        "OD"},
                {negate_token,    "NEG"},
                {absolute_token,  "ABS"}
        };
FILE *fp;
char ch; // Lưu Ký tự đọc vào từ chương trình nguôn
char retract; // Cờ báo cho biết đã đọc quá 1 ký tự sẽ nhận: true=1, false=0
token look_ahead; // Từ tố của từ vựng vừa phân tích
string ident_lexeme; // Xâu chứa từ vựng tên
int num_value; // Giá trị của từ vựng số

//--Phần phân tích từ vựng
void initialise_scanner(void) {
    char filename[20];
    printf("Nhap vao ten chuong trinh nguon:");
    gets(filename);
    if ((fp = fopen(filename, "rt")) == NULL) {
        printf("Khong the mo duoc file nay:"); //exit(1);
    }
    ch = ' ';
}

void next_character() {
    ch = fgetc(fp); //Đọc một ký tự vào từ chương trình nguồn và đặt vào biến ch
    if (ch == EOF)  //Nếu đọc hết file thì đóng lại
        fclose(fp);
}

token look_up(string ident_lexeme) { // Trả lại từ tố của từ khóa đang nằm trong biến ident_lexeme
    int i;
    for (i = 0; i < 17; i++) //Quét tất cả 17 từ khóa trong bảng
        if (0 == strcasecmp(ident_lexeme, keywtb[i].irep))
            return keywtb[i].erep;
    return err_token;
}

//Phân tích tên và kiểm tra xem có phải là từ khóa hay không. Trả về từ tố
//ident_token hoặc từ tố theo từ khóa, xâu tên được đặt trong ident_lexeme
void identifier(void) {
    int index = 0;
    do {
        ident_lexeme[index++] = ch;
        next_character();
    } while (isalpha(ch) || isdigit(ch));
    ident_lexeme[index] = 0; //Thêm ký tự kết thúc xâu
    look_ahead = look_up(ident_lexeme);
    if (look_ahead == err_token)
        look_ahead = ident_token;
    retract = true;
}

// Đoán nhận số. Hàm này cũng tính luôn giá trị của số và đặt vào num_value
void number(void) {
    num_value = 0;
    do {
        num_value = num_value * 10 + ch - '0';
        next_character();
    } while (isdigit(ch));
    look_ahead = num_token;
    retract = true;
}

//Loại bỏ các chú thích
void comment(void) {
    do
        next_character();
    while (ch != '}');
}

//Thủ tục chính của phân tích từ vựng, tìm từ tố tiếp theo
void next_token(void) {
    retract = false;
    //Loại bỏ các ký tự trắng, cách, tab, xuống dòng, chú thích
    while ((ch <= ' ' || ch == '{') && ch != EOF) {
        if (ch == '{') comment();
        next_character();
    }
    if (ch == EOF) return;
    switch (ch) {
        case '(':
            look_ahead = open_token;
            break;
        case ')':
            look_ahead = close_token;
            break;
        case ',':
            look_ahead = list_token;
            break;
        case '.':
            look_ahead = period_token;
            break;
        case ';':
            look_ahead = separator_token;
            break;
        case ':':
            next_character();
            if (ch == '=') look_ahead = become_token;
            break;
        case '+':
            look_ahead = plus_token;
            break;
        case '-':
            look_ahead = minus_token;
            break;
        case '*':
            look_ahead = times_token;
            break;
        case '/':
            look_ahead = over_token;
            break;
        case '|':
            look_ahead = modulo_token;
            break;
        case '=':
            look_ahead = equal_token;
            break;
        case '<':
            next_character();
            if (ch == '>') look_ahead = not_equal_token;
            else if (ch == '=') look_ahead = less_or_equal_token;
            else {
                look_ahead = less_than_token;
                retract = true;
            }
            break;
        case '>':
            next_character();
            if (ch == '=') look_ahead = greater_or_equal_token;
            else {
                look_ahead = greater_than_token;
                retract = true;
            }
            break;
        default:
            if (isalpha(ch))
                identifier();
            else if (isdigit(ch))
                number();
    }
    if (!retract) next_character();
}

int main() {
    //Khai báo tên ứng với thứ tự các từ tố để in theo dõi
    char *tokenname[] = {"ident_token", "num_token", "begin_token", "end_token",
                         "int_token", "var_token", "procedure_token", "call_token", "read_token",
                         "write_token", "if_token", "then_token", "else_token", "fi_token",
                         "while_token", "do_token", "od_token", "negate_token", "absolute_token",
                         "open_token", "close_token", "list_token", "period_token",
                         "separator_token", "become_token", "plus_token", "minus_token",
                         "times_token", "over_token", "modulo_token", "equal_token",
                         "not_equal_token", "less_than_token", "less_or_equal_token",
                         "greater_than_token", "greater_or_than_token", "err_token"};
    initialise_scanner();
    //Phân tích từ tố cho chương trình viết bằng SLANG và in ra mọi từ tố
    while (ch != EOF) {
        //next_character();
        //printf("%c",ch);
        next_token();
        if (look_ahead == ident_token)
            printf("\n<%s, %s>", tokenname[look_ahead], ident_lexeme);
        else if (look_ahead == num_token)
            printf("\n<%s, %d>", tokenname[look_ahead], num_value);
        else
            printf("\n<%s,>", tokenname[look_ahead]);
        //Chỉ làm việc đến dấu chấm hêt chương trình và bỏ qua phần còn lại
        if (look_ahead == period_token)
            break;
    }
}

