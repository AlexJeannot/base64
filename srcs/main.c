#include "../incs/base64.h"

u_int8_t is_last_block(u_int64_t total_block, u_int64_t current_block)
{
    if (total_block == (current_block + 1))
        return (TRUE);
    return (FALSE);
}

int main(int argc, char **argv)
{
    (void)argc;
    t_message_base64 msg;

    bzero(&msg, sizeof(t_message_base64));

    process_file(&msg, argv[1]);

    if (ENCODING)
        process_encoding(&msg);
    else if (DECODING)
        process_decoding(&msg);


    clean_msg(&msg);
}