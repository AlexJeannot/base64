#include "../incs/base64.h"

void    bytes_join(t_message_base64 *msg, char *buf, u_int64_t buf_length)
{
    char    *new_msg;

    if (!(new_msg = (char *)malloc(msg->rc_size + buf_length)))
        fatal_error(msg, "File bytes memory allocation");
    bzero(new_msg, (msg->rc_size + buf_length));

    memcpy(new_msg, msg->raw_content, msg->rc_size);
    memcpy(&(new_msg[msg->rc_size]), buf, buf_length);

    if (msg->raw_content)
        free(msg->raw_content);
    msg->raw_content = new_msg;
    msg->rc_size += buf_length;
}

int32_t     get_file(t_message_base64 *msg, char *path)
{
    int32_t fd;

    if ((fd = open(path, O_RDONLY)) == -1)
        fatal_error(msg, "file opening");
    return (fd);
}

void get_file_content(t_message_base64 *msg, int32_t fd)
{
    // t_message   *msg;
    ssize_t     ret;
    char        buf[65535];

    bzero(&buf[0], 65535);
    while ((ret = read(fd, buf, 65534)) > 0) {
        buf[ret] = '\0';
        bytes_join(msg, &buf[0], ret);
        bzero(&buf[0], 65535);
        // printf("ret = %zd\n", ret);
    }
    if (ret == -1)
        fatal_error(msg, "file reading");
}

// void        set_file_context(t_message *msg, char *path)
// {
//     msg->src_type = SRC_FILE;

//     if (!(msg->src = (char *)malloc(ft_strlen(path) + 1)))
//         fatal_error("file source memory allocation");
//     bzero(msg->src, (ft_strlen(path) + 1));

//     ft_strncpy(msg->src, path, ft_strlen(path));
// }

void process_file(t_message_base64 *msg, char *path)
{
    int32_t     fd;

    fd = get_file(msg, path);
    get_file_content(msg, fd);
    // set_file_context(msg, path);
    if (close(fd) == -1)
        fatal_error(msg, "file descriptor closing");
}