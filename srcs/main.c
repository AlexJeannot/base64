#include "../incs/base64.h"

typedef struct s_shift_block
{
    u_int8_t a;
    u_int8_t b;
    u_int8_t c;
}           t_shift_block;

void print_char(u_int8_t nb)
{
    if (nb <= 25)
        printf("%c", 'A' + nb);
    else if (nb > 25 && nb <= 51)
        printf("%c", 'a' + (nb - 26));
    else if (nb > 51 && nb <= 61)
        printf("%c", '0' + (nb - 52));
    else if (nb == 62)
        printf("%c", '+');
    else if (nb == 63)
        printf("%c", '/');
}

int main(int argc, char **argv)
{
    (void)argc;
    t_message msg;

    bzero(&msg, sizeof(t_message));
    process_file(&msg, argv[1]);

    // u_int64_t nb_blocks;

    printf("msg.rc_size = %lu\n", msg.rc_size);

    msg.fc_size = msg.rc_size + (3 - (msg.rc_size % 3));
    printf("msg.fc_size = %lu\n", msg.fc_size);

    // nb_blocks = (msg.rc_size / 3);
    // nb_blocks += (msg.rc_size % 3) ? 1 : 0;
    // nb_blocks *= 4;
    // printf("nb_blocks = %lu\n", nb_blocks);

    char c;
    u_int8_t b;
    for (u_int64_t count = 0; count < msg.rc_size; count++)
    {
        c = msg.raw_content[count];
        for (int64_t bit = 7; bit >= 0; bit--)
        {
            b = (c >> bit) & 0b00000001;
            printf("%u", b);
        }
        printf(" ");
        if (count != 0 && (count + 1) % 8 == 0)
            printf("\n");
    }
    printf("\n");

    // u_int8_t var;

    u_int64_t nb_shift_block = msg.fc_size / 3;
    printf("nb_shift_block = %lu\n", nb_shift_block);

    t_shift_block *s_block;

    if (!(msg.fmt_content = (char *)malloc(msg.fc_size)))
        fatal_error(&msg, "formated content memory allocation");
    
    bzero(msg.fmt_content, msg.fc_size);
    memcpy(msg.fmt_content, msg.raw_content, msg.rc_size);

    for (u_int64_t count = 0; count < nb_shift_block; count++)
    {
        s_block = (t_shift_block *)msg.fmt_content + count;
        // for (u_int64_t c2 = 0; c2 < 4; c2++)
        // {
            // var = s_block->a & 0b11111100;
        
        print_char((s_block->a & 0b11111100) >> 2);
        if ()
        print_char(((s_block->a & 0b00000011) << 4) | ((s_block->b & 0b11110000) >> 4));
        print_char(((s_block->b & 0b00001111) << 2) | ((s_block->c & 0b11000000) >> 6));
        print_char(s_block->c & 0b00111111);
            // print_char(s_block->a & 0b11111100);
            // print_char(s_block->a & 0b11111100);

        // }



        // var = (u_int8_t)(msg.raw_content[0] & 0b11111100);
        // var = (u_int8_t)(*s_block & 0b11111100);

        

        // msg.raw_content = msg.raw_content << 6;
        // for (int64_t bit = 7; bit >= 0; bit--)
        // {
        //     b = (var >> bit) & 0b00000001;
        //     printf("%u", b);
        // }
        // printf("\n------------------------------\n");
    }
    printf("\n");
}