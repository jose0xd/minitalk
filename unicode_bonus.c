#include <stdlib.h>
#include <unistd.h>

// Return size of unicode. 0 if continuation byte.
int	ft_len_utf8(unsigned char byte)
{
	int	len;

	if (byte < 0x80)
		len = 1;
	else if (byte < 0xc0)
		len = 0;
	else if (byte < 0xe0)
		len = 2;
	else if (byte < 0xf0)
		len = 3;
	else
		len = 4;
	return (len);
}

static void	ft_clean_uchar(unsigned char *c)
{
	int	i;

	i = 3;
	while (i >= 0)
		c[i--] = 0;
}

void	ft_put_uchar(unsigned char byte)
{
	static int				len;
	static unsigned char	c[4];
	static int				i = 0;

	if (!ft_len_utf8(byte))
	{
		if (i >= 4)
			exit(EXIT_FAILURE); // TODO
		c[i++] = byte;
		if (len == i + 1)
			write(1, c, len);
		return ;
	}
	len = ft_len_utf8(byte);
	ft_clean_uchar(c);
	i = 0;
	c[i++] = byte;
	if (len == 1)
		write(1, c, len);
}
