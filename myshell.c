#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main() {
  
  int ct = 0;
  while(1) {
    printf("(%d) >_ ",++ct);
   
    char buffer[1024];
    char* temp;
    char* token;

    char* argv[1024];
    int status;
    pid_t pid;
    int i = 1;

    fgets(buffer, 1024, stdin);
    temp  = strtok(buffer," \n\t()<>|&;");
    argv[0] = temp;

    if(strcmp(argv[0],"exit") == 0) {
	exit(0);
    }
    else if(strcmp(argv[0],"cd") == 0) {
      if(chdir(strtok(NULL," \n\t()<>|&;")) != 0) {
	if(errno == EACCES)
	  perror("Search permission denied\n");
	else if(errno == EFAULT)
	  perror("path points outside of your address space\n");
	else if(errno == EIO)
	  perror("an IO error occured\n");
	else if(errno == ELOOP)
	  perror("Too many symbolic links were encountered in resolving path\n");
	else if(errno == ENAMETOOLONG)
	  perror("path is too long\n");
	else if(errno == ENOENT)
	  perror("the file does not exist\n");
	else if(errno == ENOMEM)
	  perror("insufficient kernel memory available\n");
	else if(errno == ENOTDIR)
	  perror("a component of path is not a directory\n");
      }
    }
    else if((pid = fork())==0) {//(token = strtok(NULL," \n\t()<>|&;")) == NULL) { //if there is not another agrument
      
      while((token = strtok(NULL," \n\t()|&;")) != NULL){
	if(strcmp(token,">") == 0) {
	  //set freopen to the file 
	  token = strtok(NULL," \n\t()|&;");
	  if(freopen(token,"w",stdout) == NULL){ //current output is file
	    if(errno == EACCES)
	      perror("Search permission is denied for one of the components of path\n");
	    else if(errno == EFAULT)
	      perror("path points outside your accessible address space\n");
	    else if(errno == EIO)
	      perror("an I/O error occured\n");
	    else if(errno == ELOOP)
	      perror("too many symbolic links were encountered in resolving path\n");
	    else if(errno == ENAMETOOLONG)
	      perror("path is too long\n");
	    else if(errno == ENOENT)
	      perror("file does not exist");
	    else if(errno == ENOMEM)
	      perror("Insufficient kernel memory available\n");
	    else if(errno == ENOTDIR)
	      perror("A component of path is not a directory\n");
	    else if(errno == EINVAL)
	      perror("File not found\n");
	  }
	}
	else if(strcmp(token,"<") == 0) { // 6. redirects input from the file and write output to the file
	  token = strtok(NULL," \n\t()|&;");// input and output redirection
	  if(freopen(token,"r",stdin) == NULL) {
	    if(errno == EINVAL)
	      perror("File not found\n");
	    else if(errno == EACCES)
	      perror("Search permission is denied for one of the components of path\n");
	    else if(errno == EFAULT)
	      perror("path points outside your accessible address space\n");
	    else if(errno == EIO)
	      perror("an I/O error occured\n");
	    else if(errno == ELOOP)
	      perror("too many symbolic links were encountered in resolving path\n");
	    else if(errno == ENAMETOOLONG)
	      perror("path is too long\n");
	    else if(errno == ENOENT)
	      perror("file does not exist\n");
	    else if(errno == ENOMEM)
	      perror("Insufficient kernel memory available\n");
	    else if(errno == ENOTDIR)
	      perror("A component of path is not a directory\n");
	    
	  } // reads input from file
	  if(freopen(token,"w",stdout)== NULL) {
	    if(errno == EINVAL)
	      perror("File not found\n");
	    else if(errno == EACCES)
	      perror("Search permission is denied for one of the components of path\n");
	    else if(errno == EFAULT)
	      perror("path points outside your accessible address space\n");
	    else if(errno == EIO)
	      perror("an I/O error occured\n");
	    else if(errno == ELOOP)
	      perror("too many symbolic links were encountered in resolving path\n");
	    else if(errno == ENAMETOOLONG)
	      perror("path is too long\n");
	    else if(errno == ENOENT)
	      perror("file does not exist\n");
	    else if(errno == ENOMEM)
	      perror("Insufficient kernel memory available\n");
	    else if(errno == ENOTDIR)
	      perror("A component of path is not a directory\n");
	  } //writes output to the file
	}
	else if(strcmp(token,">>") == 0) { //appends output to a file
	  token = strtok(NULL, " \n\t()|&;");
	  if(freopen(token,"a+",stdout) == NULL) {
	    if(errno == EINVAL)
	      perror("File not found\n");
	    else if(errno == EACCES)
	      perror("Search permission is denied for one of the components of path\n");
	    else if(errno == EFAULT)
	      perror("path points outside your accessible address space\n");
	    else if(errno == EIO)
	      perror("an I/O error occured\n");
	    else if(errno == ELOOP)
	      perror("too many symbolic links were encountered in resolving path\n");
	    else if(errno == ENAMETOOLONG)
	      perror("path is too long\n");
	    else if(errno == ENOENT)
	      perror("file does not exist\n");
	    else if(errno == ENOMEM)
	      perror("Insufficient kernel memory available\n");
	    else if(errno == ENOTDIR)
	      perror("A component of path is not a directory\n");
	    
	  } //writes output to end of file
	}
	else {
	  argv[i] = token;
	  i++;
	}
      }
      
      execvp(argv[0],argv);
      if(errno == E2BIG)
	perror("arguments are too large\n");
      else if(errno == EACCES)
	perror("Permission denied\n");
      else if(errno == EFAULT)
	perror("file points to outside of your address space\n");
      else if(errno == EINVAL)
	perror("more than one interpreter\n");
      else if(errno == EIO)
	perror("I/O error occurred\n");
      else if(errno == EISDIR)
	perror("ELF interpreter was a directory\n");
      else if(errno == ELIBBAD)
	perror("ELF interpreter not in recognizable format.\n");
      else if(errno == ELOOP)
	perror("too many symbolic links encountered\n");
      else if(errno == EMFILE)
	perror("max number of files open\n");
      else if(errno == ENAMETOOLONG)
	perror("filename is too long\n");
      else if(errno == ENFILE)
	perror("System limit on total number of fies has been reached\n");
      else if(errno == ENOENT)
	perror("filename or ELF does not exist\n");
      else if(errno == ENOEXEC)
	perror("executable is not in recognized format\n");
      else if(errno == ENOMEM)
	perror("Insufficient kernel memory available\n");
      else if(errno == ENOTDIR)
	perror("component on path is not a directory\n");
      else if(errno == EPERM)
	perror("User is not superuser.\n");
      else if(errno == ETXTBSY)
	perror("executable was open for writing by more than one process\n");
      
      exit(errno);
    }
    else if(pid < 0) {
      if(errno == EAGAIN)
	perror("cannot allocate sufficient memory\n");
      else if(errno == ENOMEM)
	perror("could not allocate -- memory is tight\n");
      else if(errno == ENOSYS)
	perror("fork is not supported on this platform\n");
      exit(errno);//exit with errno
    }
    else {
      while(wait(&status) != pid);//wait for child to terminate
    }
    
  } //end while
  
  return 0;
}
