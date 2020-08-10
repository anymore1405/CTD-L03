// Phần khai báo của bộ phân tích từ vựng
#define max_ident_length 255
typedef char string[max_ident_length + 1];
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
typedef struct keyword {
    token erep;    // Từ tố của từ Khóa
    char irep[8]; // Mẫu từ khóa
};
