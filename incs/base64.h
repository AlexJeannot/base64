#ifndef BASE64
# define BASE64

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <strings.h>
# include <string.h>

# define FALSE 0
# define TRUE 1
# define ERROR 2
# define INPUT 3
# define OUTPUT 4

typedef struct  s_message
{
    char                *raw_content;
    char                *fmt_content;
    char                *processed_content;
    u_int64_t           rc_size;
    u_int64_t           fc_size;
    u_int64_t           pc_size;
    u_int64_t           cc_size;
    u_int64_t           blocks_size;
}               t_message;

typedef struct s_block
{
    u_int8_t a;
    u_int8_t b;
    u_int8_t c;
}           t_block;

typedef struct s_args
{
    u_int8_t d;
    u_int8_t e;
    u_int8_t i;
    u_int8_t o;
    u_int8_t n;
    char *input;
    char *output;
}   t_args;

void fatal_error(t_message *msg, const char *reason);
// void process_file(t_message *msg, char *path);


void        clean_msg(t_message *msg);
int32_t     get_file(t_message *msg, char *path, u_int8_t type);

u_int8_t is_last_block(u_int64_t total_block, u_int64_t current_block);
void process_encoding(t_message *msg, t_args *args);
void process_decoding(t_message *msg, t_args *args);

void        parse_args(int nb_args, char **list_args, t_message *msg, t_args *args);

void get_content(t_message *msg, t_args *args);
void    args_error(t_message *msg, const char *reason, const char *input);

#endif