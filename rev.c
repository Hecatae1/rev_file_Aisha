
/*Aisha Abdullahi
12 Febuary 2025*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

void check_num_args(int argc, char *argv[]); // gpt implicit error declaration of function
void check_src_file_is_regular(const char *argv);
void copy_src_to_dest(const char *src, const char *dest);


int main(int argc, char *argv[])
{ 

	/* These functions each call exit(-1) if there is a problem. */
	check_num_args(argc, argv);
	check_src_file_is_regular(argv[1]);
	copy_src_to_dest(argv[1], argv[2]);
	return 0;   /* no error */
}

void check_num_args(int argc, char *argv[])
{
    if (argc !=3){
        fprintf(stderr, "Incorrect argument: ");
        for (int i = 0; i < argc; i++) {
        fprintf(stderr," %s, ", argv[i]);
        }
        fprintf(stderr, "\n Try '<./rev src dest>'\n");
        exit(-1);
    }

}
// from pubs.opengroup.org/onlinepubs/7908799/xsh/sysstat.h.html
void check_src_file_is_regular(const char *argv){
    struct stat file;
    if (stat(argv, &file) == -1){
        if ((!S_ISREG(file.st_mode))){
             fprintf(stderr, "'%s' ERROR!\n This isn't a regular file.\n", argv);
             fprintf(stderr, "File size: %ld bytes\n", (long)file.st_size);
             exit(-1);
        }
    }
    if (stat(argv, &file) == 0) {
        if (file.st_size == 0) {
            fprintf(stderr, "Error: The file is empty.\n");
            exit(-1);
        }
    }
}
void copy_src_to_dest(const char *src, const char *dest)
{
    FILE *input = fopen(src, "r");
    FILE *output = fopen(dest, "w");

        if (input == NULL || output == NULL) {
        fprintf(stderr, "Error opening input or output file\n");
        exit(-1);
    }
//labex.io/tutorials/c-reverse-content-of-file-using-c-123317

    // make the file pointer to end to read file in reverse
    fseek(input, 0, SEEK_END);
    if (fseek(input, 0, SEEK_END) != 0)
    {
        fprintf(stderr,"Error seeking to end of file");
        fclose(input);
        fclose(output);
        exit(-1);
    }

    long ch = ftell(input); // find the current position
    while (--ch >= 0)
    {
        
        fseek(input, ch, SEEK_SET);
        if (fseek(input, ch, SEEK_SET) != 0)
        {
            perror("Cannot reach specified location location");
            fclose(input);
            fclose(output);
            exit(-1); //
        }
        char c = fgetc(input);
        
        if (c == EOF)
        { // Handle the error,  found something similar at https://stackoverflow.com/questions/11805758/fclose-always-returns-eof
            perror("Cannot read from source file");
            fclose(input);
            fclose(output);
            exit(-1);
        }
        if (fputc(c, output) == EOF)
        {
            perror("Cannot write todestination file");
            fclose(input);
            fclose(output);
            exit(-1);
        } 
    }
   
    fclose(input); // close sorce file
    fclose(output); // close destination file
   
}

