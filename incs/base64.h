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

typedef struct  s_message
{
    char                *raw_content;
    char                *fmt_content;
    char                *src;
    char                *hash;
    u_int64_t           rc_size;
    u_int64_t           fc_size;
    u_int64_t           cc_size;
    u_int8_t            nofile;
    u_int8_t            src_type;
    struct  s_message   *next;
}               t_message;

void        process_file(t_message   *msg, char *path);
void    fatal_error(t_message *msg, const char *reason);

// t_message   *allocate_msg(void);
void        clean_msg(t_message *msg);
void        clean_all_msg(void);
int32_t     get_file(t_message *msg, char *path);

#endif