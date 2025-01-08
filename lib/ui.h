#ifndef ui_h
#define ui_h


void flush(char *notice, char **arr, int length, int *choice);
void result_attach(char *result, int *result_colour, char *notice, char **arr, int length, int *choice);
int ui_re_choice(char *notice, char **arr, int length, char *result, int result_colour);
void orginize_input(int *choice, int *satus, const int *length);
int ui_choice(char *notice, char **arr, int length);


#endif
