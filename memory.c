#include <stdio.h>
#include <string.h>

#define ROW_LIMIT 16
#define CHAR_LOWER 33
#define CHAR_UPPER 126

void memory_print(void* ptr, size_t size);
void print_row_hex(void* row_ptr, int row_size);
void print_row_char(void* row_ptr, int row_size);

void main()
{

  char test[] = "This is just some random text to make sure that everything works fine in this memory printer.";

  memory_print(test, (size_t)strlen(test));
  printf("\n");
  return;

} 

void memory_print(void* ptr, size_t buffer_size)
{
  
  int current_row = 0;

  while (buffer_size > 0)
  {

    int row_size = (buffer_size > ROW_LIMIT ? ROW_LIMIT : buffer_size);
    void* row_ptr = ptr + current_row * ROW_LIMIT;

    printf("\n%04x  ", (int)row_ptr);      // print buffer row address
    print_row_hex(row_ptr, row_size);      // print buffer row as hexadecimals
    print_row_char(row_ptr, row_size);     // print buffer row as chars

    buffer_size = (buffer_size > ROW_LIMIT ? buffer_size - ROW_LIMIT : 0);
    current_row++;

  }

}

void print_row_hex(void* row_ptr, int row_size)
{

  for (int i = 0; i < ROW_LIMIT; i++)
  {

    (row_size > 0) ? printf("%02hhX ", *((int*)(row_ptr + i))) : printf("00 ");
    if (i == 7 || i == 15) printf(" ");
    row_size--;

  }

}

void print_row_char(void* row_ptr, int row_size)
{

  for (int i = 0; i < row_size; i++)
  {

    ( *(char*)(row_ptr + i) >= (char)CHAR_LOWER &&
      *(char*)(row_ptr + i) <= (char)CHAR_UPPER )
       ? printf("%c", *(char*)(row_ptr + i))
       : printf("."); 

    if (i == 7) printf(" ");
  }

}
