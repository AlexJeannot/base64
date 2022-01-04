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
    t_message msg;
    t_args args;

    bzero(&msg, sizeof(t_message));
    bzero(&args, sizeof(t_args));

    parse_args(argc - 1, &argv[1], &msg, &args);
    get_content(&msg, &args);

    if (args.e)
        process_encoding(&msg, &args);
    else
        process_decoding(&msg, &args);

    clean_msg(&msg);
}