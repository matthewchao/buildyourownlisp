// #include <stdio.h>

// static char input[2048];

// int main(int argc, char** argv) {
//     puts("Lispy Version 0.0.0.0.1");
//     puts("Press Ctrl+c to Exit\n");

//     while (1) {
//         fputs("lispy> ",stdout);

//         fgets(input,2048,stdin);

//         printf("No you're a %s",input);
//     }

//     // return 0;
// }



//VERSION 2 BELOW, WHICH ALLOWS UP/DOWN KEYS TO BE USED TO SEE HISTORY
//following http://www.buildyourownlisp.com/chapter4_interactive_prompt
#include <stdio.h>
#include <stdlib.h>

/* If we are compiling on Windows compile these functions */
#ifdef _WIN32
#include <string.h>

static char buffer[2048];

/* Fake readline function */
char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
}

/* Fake add_history function */
void add_history(char* unused) {}

/* Otherwise include the editline headers */
#else


//note was getting error for the libraries not being found;
//tried installing libedit-dev
//now getting "undefined reference to 'readline'"
//added -ledit compilation flag and it compiled!
#include <editline/readline.h>


// but actually the up/down completion still wasn't working;
// until I commented below:
// #include <editline/history.h>
#endif


int main(int argc, char** argv) {

  /* Print Version and Exit Information */
  puts("Lispy Version 0.0.0.0.1");
  puts("Press Ctrl+c to Exit\n");

  /* In a never ending loop */
  while (1) {

    /* Output our prompt and get input */
    char* input = readline("lispy> ");

    /* Add input to history */
    add_history(input);

    /* Echo input back to user */
    printf("No you're a %s\n", input);

    /* Free retrieved input */


    // I tried running with the following line commented:
    //and valgrind --leak-check=full --show-leak-kinds=all ./prompt
    //detects an error
    free(input);

  }


  return 0;
}
