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

typedef struct  s_message_base64
{
    char                *raw_content;
    char                *fmt_content;
    char                *processed_content;
    u_int64_t           rc_size;
    u_int64_t           fc_size;
    u_int64_t           pc_size;
    u_int64_t           cc_size;
    u_int64_t           blocks_size;
}               t_message_base64;

typedef struct s_block
{
    u_int8_t a;
    u_int8_t b;
    u_int8_t c;
}           t_block;



void fatal_error(t_message_base64 *msg, const char *reason);
void process_file(t_message_base64 *msg, char *path);


void        clean_msg(t_message_base64 *msg);


u_int8_t is_last_block(u_int64_t total_block, u_int64_t current_block);
void process_encoding(t_message_base64 *msg);
void process_decoding(t_message_base64 *msg);


#endif