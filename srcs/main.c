#include "../incs/base64.h"

u_int8_t is_last_block(u_int64_t total_block, u_int64_t current_block)
{
    if (total_block == (current_block + 1))
        return (TRUE);
    return (FALSE);
}

void format_msg(t_message_base64 *msg)
{
    msg->fc_size = (!(msg->rc_size % 3)) ? msg->rc_size : msg->rc_size + (3 - (msg->rc_size % 3));

    if (msg->rc_size == msg->fc_size)
        msg->fmt_content = msg->raw_content;
    else {
        if (!(msg->fmt_content = (char *)malloc(msg->fc_size)))
            fatal_error(msg, "formated content memory allocation");
        
        bzero(msg->fmt_content, msg->fc_size);
        memcpy(msg->fmt_content, msg->raw_content, msg->rc_size);
    }
}

void prepare_output_encoded(t_message_base64 *msg)
{
    msg->pc_size = msg->fc_size + (msg->fc_size / 3);
    msg->blocks_size = msg->fc_size / 3;

    if (!(msg->processed_content = (char *)malloc(msg->pc_size + 1)))
        fatal_error(msg, "Processed content memory allocation");
    bzero(msg->processed_content, (msg->pc_size + 1));
}

void prepare_output_decoded(t_message_base64 *msg)
{
    msg->pc_size = msg->fc_size - (msg->fc_size / 4);
    msg->blocks_size = msg->pc_size / 3;

    if (!(msg->processed_content = (char *)malloc(msg->pc_size + 1)))
        fatal_error(msg, "Processed content memory allocation");
    bzero(msg->processed_content, (msg->pc_size + 1));
}

int main(int argc, char **argv)
{
    (void)argc;
    t_message_base64 msg;

    bzero(&msg, sizeof(t_message_base64));
    process_file(&msg, argv[1]);
    format_msg(&msg);

    prepare_output_decoded(&msg);
    decode_msg_base64(&msg);

    // prepare_output_encoded(&msg);
    // encode_msg_base64(&msg);

    // printf("%s\n", msg.processed_content);

    for (u_int64_t count = 0; count < msg.pc_size; count++)
    {
        write(1, &msg.processed_content[count], 1);
    }

    // clean_msg(&msg);
}