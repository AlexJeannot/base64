#include "../incs/base64.h"

#include "../incs/base64.h"

u_int8_t add_decoded_char(char encoded_char)
{
    u_int8_t bits;

    bits = '\0';
    if (encoded_char >= 'A' && encoded_char <= 'Z')
        bits = encoded_char - 65;
    else if (encoded_char >= 'a' && encoded_char <= 'z')
        bits = encoded_char - 71;
    else if (encoded_char >= '0' && encoded_char <= '9')
        bits = encoded_char + 4;
    else if (encoded_char == '+')
        bits = 62;
    else if (encoded_char == '/')
        bits = 63;
    else if (encoded_char == '=')
        bits = 0;

    //printf("bits = %u\n", bits);
    return (bits);
    //msg->processed_content[msg->cc_size++] = encoded_char;
}

// void add_complement(t_message_base64 *msg)
// {
//     msg->processed_content[msg->cc_size++] = '=';
// }

void set_first_char(t_block *block, u_int8_t bits)
{
    block->a = (bits << 2);
    // return ((block->a & 0b11111100) >> 2);
}

void set_second_char(t_block *block, u_int8_t bits)
{
    block->a = (bits & 0b00110000) >> 4 | block->a;
    block->b = (bits & 0b00001111) << 4;
    // return (((block->a & 0b00000011) << 4) | ((block->b & 0b11110000) >> 4));
}

void set_third_char(t_block *block, u_int8_t bits)
{
    block->b = (bits & 0b00111100) >> 2 | block->b;
    block->c = (bits & 0b00000011) << 6;
    // return (((block->b & 0b00001111) << 2) | ((block->c & 0b11000000) >> 6));
}

void set_fourth_char(t_block *block, u_int8_t bits)
{
    block->c = bits | block->c;
    // return (block->c & 0b00111111);
}

void decode_msg_base64(t_message_base64 *msg)
{
    t_block *block;

    // printf("msg->blocks_size = %lu\n", msg->blocks_size);

    for (u_int64_t count = 0; count < msg->blocks_size; count++)
    {
        block = (t_block *)msg->processed_content + count;
        // add_decoded_char(msg, msg->fmt_content[count]);

        set_first_char(block, add_decoded_char(msg->fmt_content[count * 4]));
        set_second_char(block, add_decoded_char(msg->fmt_content[1 + count * 4]));
        set_third_char(block, add_decoded_char(msg->fmt_content[2 + count * 4]));
        set_fourth_char(block, add_decoded_char(msg->fmt_content[3 + count * 4]));
        // printf("msg->processed_content = %s\n", msg->processed_content);

        if (is_last_block(msg->blocks_size, count))
        {
            if (!add_decoded_char(msg->fmt_content[2 + count * 4]))
                msg->pc_size--;
            if (!add_decoded_char(msg->fmt_content[3 + count * 4]))
                msg->pc_size--;
        }

        // add_decoded_char(msg, msg->fmt_content[count]);
        // if (is_last_block(msg->blocks_size, count)) {
        //     if (!get_third_char(block))
        //         add_complement(msg, msg->fmt_content[count]);
        //     else
        //         add_decoded_char(msg, msg->fmt_content[count]);

        //     if (!get_fourth_char(block))
        //         add_complement(msg, msg->fmt_content[count]);
        //     else
        //         add_decoded_char(msg, msg->fmt_content[count]);
        // }
        // else
        // {
        // add_decoded_char(msg, msg->fmt_content[count]);
        // add_decoded_char(msg, msg->fmt_content[count]);
        // }
    }
}