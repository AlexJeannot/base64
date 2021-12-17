#include "../incs/base64.h"

void    fatal_error(t_message_base64 *msg, const char *reason)
{
    printf("Error: %s\n", reason);
    clean_msg(msg);
    exit(1);
}

// void    args_error(const char *reason, const char *input)
// {
//     if (input)
//         printf("Error: %s [%s]\n", reason, input);
//     else
//         printf("Error: %s\n", reason);
    // display_help();
    // clean_all_msg();
    // exit(1);
// }