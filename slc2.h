// Phần khai báo của bộ phân tích từ vựng
#define max_ident_length 255
typedef char string[max_ident_length+1];
//liệt kê và đánh số thứ tự các từ tố
typedef enum {
   ident_token, num_token, begin_token, end_token, int_token, var_token,
   procedure_token, call_token, read_token, write_token, if_token, then_token,
   else_token, fi_token, while_token, do_token, od_token, negate_token,
   absolute_token, open_token, close_token, list_token, period_token,
   separator_token, become_token, plus_token, minus_token, times_token, over_token,
   modulo_token, equal_token, not_equal_token, less_than_token,
   less_or_equal_token, greater_than_token, greater_or_equal_token, err_token
  } token;
typedef struct {
   token erep;    // Từ tố của từ Khóa
   char irep[8]; // Mẫu từ khóaoken
  }keyword;

//Khai báo thủ tục trước khi dùng
void block(void);
void declaration_part(void);
void constant_declaration(void);
void type_declarer(void);
void variable_declaration(void);
void procedure_declaration(void);
void statement_part(void);
void statement(void);
void assignment_statement(void);
void left_part(void);
void if_statement(void);
void while_statement(void);
void call_statement(void);
void read_statement(void);
void write_statement(void);
void for_statement(void);
void expression(void);
void term(void);
void factor(void);
void operand(void);
void add_operator(void);
void multiply_operator(void);
void unary_operator(void);
void relation(void);
void relation_operator(void);
