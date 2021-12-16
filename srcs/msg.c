#include "../incs/base64.h"

// t_message   *allocate_msg(void)
// {
//     t_message   *new_msg;
//     t_message   *tmp_msg;

//     tmp_msg = NULL;
//     if (!(new_msg = (t_message *)malloc(sizeof(t_message))))
//         fatal_error("message memory allocation");
//     bzero(new_msg, sizeof(t_message));

//     if (!list_msg)
//         list_msg = new_msg;
//     else {
//         tmp_msg = list_msg;
//         while (tmp_msg->next)
//             tmp_msg = tmp_msg->next;
//         tmp_msg->next = new_msg; 
//     }
//     return (new_msg);
// }

// void        clean_all_msg(void)
// {
//     t_message   *tmp;

//     tmp = list_msg;
//     while (tmp) {
//         clean_msg(tmp);
//         tmp = tmp->next;
//     }
// }

void        clean_msg(t_message *msg)
{
    if (msg->raw_content)
        free(msg->raw_content);
    if (msg->fmt_content)
        free(msg->fmt_content);
    if (msg->src)
        free(msg->src);
    if (msg->hash)
        free(msg->hash);
}