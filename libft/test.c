
#include "libft.h"

int		main(int argc, char **argv)
{
	int		inner;
	int		limit;
	int		outer;
	char	***arr;
	char	**av;

	inner = 0;
	limit = 0;
	outer = 0;
	arr = NULL;
	av = ft_cpyarr(argv + 1);
	if (argc < 2)
		return (0);
	while (av[inner])
	{
		if (!ft_strcmp(av[inner], "|"))
			limit++;
		inner++;
	}
	arr = (char ***)malloc(sizeof(char **) * (limit + 2));
	if (!arr)
		return (ft_printf("malloc error\n"));
	inner = 0;
	limit = 0;
	while (av[inner])
	{
		if (!ft_strcmp(av[inner], "|"))
		{
			arr[outer] = ft_cpynarr(av + limit, (inner - limit));
			limit = inner + 1;
			outer++;
		}
		inner++;
	}
	arr[outer] = ft_cpyarr(av + limit);
	arr[outer + 1] = NULL;
	inner = 0;
	while (arr[inner])
	{
		ft_printarr(arr[inner]);
		inner++;
	}
	outer = 0;
	while (arr[outer])
	{
		ft_farray(arr[outer]);
		outer++;
	}
	free(arr);
	ft_farray(av);
	return (0);
}
