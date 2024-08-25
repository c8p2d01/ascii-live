#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../ft_libft/inc/libft.h"

void print_indefinetly(char **frames, int framecount);

	char	*filename;
int main(int argc, char **argv)
{
	if (argc < 2 || argc > 3)
		return (1);
	
	//file finder
	int		namelength = 0;
	char	path[] = "./frames/.go";
	int		file;

	filename = calloc(strlen(path) + strlen(argv[1]) + 1, sizeof(char));
	if (!filename)
		return (printf("memory error\n") * 0 + 1);
	memcpy(filename, path, strlen(path) - 3);
	memcpy(&filename[strlen(filename)], argv[1], strlen(argv[1]));
	memcpy(&filename[strlen(filename)], &path[strlen(path) - 3], 3);
	file = open(filename, O_RDONLY);
	if (file <= 0)
		return (printf("File >%s< not Found\n%s\n", argv[1], filename) * 0 + 1);

	char *command = calloc(368 + strlen(filename), sizeof(char));
	printf("file\t %s\n", filename);
	sprintf(command, "cat %s | grep '\\`,' | wc -l > framecount", filename);
	printf("command %s\n", command);
	system(command);

	int		fd;
	int		framecount;
	char	*num;

	fd = open("framecount", O_RDONLY);
	if (fd <= 0)
		goto error;
	num = get_next_line(fd);
	framecount = atoi(num);
	free(num);
	close(fd);

	if (num <= 0)
		return (printf("no frames found\n") * 0 + 1);

	char	**frames;
	char	*raw;
	frames = calloc(framecount + 1, sizeof(char *));
	for (int i = 0; i < framecount; i++)
	{
		raw = get_until(file, '`');
		free(raw);
		raw = get_until(file, '`');
		frames[i] = ft_strtrim(raw, "`");
		free(raw);
	}
	free(filename);
	close(file);

	print_indefinetly(frames, framecount);

error:
	if (filename)
		free(filename);
	if (command)
		free(command);
	return (1);
	
}

void _(){}
void print_indefinetly(char **frames, int framecount){
  int r = 255;
  int g = 0;
  int b = 0;
  int i;
  int f = 0;

  char	*print_color = calloc(42, sizeof(char));
  char	*print_color2 = calloc(1, 1);
  char	*copy;

  i = (r << 16 | g << 8 | b);
  while (1)
  {
    usleep(100000);
	free(print_color2);
	ft_memset(print_color, 'A', 21);
    sprintf(print_color, "\e[0m\n\e[38;2;%i;%i;%im", (i>>16), (i>>8)%256, i%256);
	print_color2 = ft_strtrim(print_color, "A");
    ((i>>16)%256 >= 255) ?
      (i%256 > 0) ? 
        i--
        :
        ((i>>8)%256 < 255) ?
          i += 256
          :
          _()
      :
      _();
    ((i>>8)%256 >= 255) ?
      ((i>>16)%256 > 0) ? 
        i -= 256 * 256
        :
        (i%256 < 255) ?
          i++
          :
          _()
      :
      _();
    (i%256 >= 255) ?
      ((i>>8)%256 > 0) ? 
        i -= 256
        :
        ((i>>16)%256 < 255) ?
          i += 256 * 256
          :
          _()
      :
      _();
	  copy = ft_strdup(frames[f++]);
	  str_sed(&copy, "\n", print_color2);
	  printf("\e[1;1H\e[2J%s\e[0m", copy);
	  free(copy);
	  f %= framecount;
  }
}