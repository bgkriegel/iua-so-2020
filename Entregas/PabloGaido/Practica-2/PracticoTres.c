#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

int main()
{
	DIR *dip;
	struct dirent *dit;
	int i = 0;

	if ((dip = opendir("/")) == NULL) {
		perror("opendir");
		return 0;
	}

	while ((dit = readdir(dip)) != NULL) {
		i++;
		printf("%s\n", dit->d_name);
	}

	if (closedir(dip) == -1) {
		perror("closedir");
		return 0;
	}

	return 1;
}
