#include "philo.h"

int	len(char const *s1)
{
	int	l;

	l = 0;
	while (s1[l])
		l++;
	return (l);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*output;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	output = (char *)malloc((len(s1) + len(s2) + 1) * sizeof(char));
	if (output == NULL)
		return (NULL);
	i = 0;
	while (i < len(s1))
	{
		output[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len(s2))
		output[i++] = s2[j++];
	output[i] = '\0';
	return (output);
}

int	count_digits(int n)
{
	int	count;

	count = 0;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*buff;
	int		digit_len;
	int		i;

	digit_len = count_digits(n);
	buff = (char *)malloc((digit_len + 1) * sizeof(char));
	if (buff == NULL)
		return (NULL); // Return NULL if memory allocation fails
	
	buff[digit_len] = '\0';
	i = digit_len - 1;
	while (n > 0)
	{
		buff[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	return (buff);
}

char	*join_str_num(char	*str,	int	num)
{
	char	*n;
	char	*res;

	n = ft_itoa(num);
	res = ft_strjoin(str, n);
	free(n);
	return (res);
}
