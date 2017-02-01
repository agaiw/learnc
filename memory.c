#include <stdio.h>
#include <string.h>

#define ROW_LIMIT 16
#define CHAR_LOWER 33
#define CHAR_UPPER 126

void memory_print(void* ptr, size_t size);

void main()
{

  char test[] = "This is just some random text to make sure that everything works fine in this memory printer.";

  memory_print(test, (size_t)strlen(test));
  return;

} 

void memory_print(void* ptr, size_t buffer_size)
{
  
  int current_row = 0;

  while (buffer_size > 0) {

    int row_size = (buffer_size > ROW_LIMIT ? ROW_LIMIT : buffer_size);
    void* row_ptr = ptr + current_row * ROW_LIMIT;

    // print buffer row address
    printf("\n%p  ", row_ptr);

    // print buffer row as hexadecimals
    int row_crawler = row_size;

    for (int i = 0; i < ROW_LIMIT; i++) {
      
      printf("%02hhX ", (row_crawler > 0) ? *((int*)(row_ptr + i)) : 0);

      if (i == 7 || i == 15) {
        printf(" ");
      }

     row_crawler--;

    }

    // print buffer row as chars
    for (int i = 0; i < row_size; i++) {

      char oneChar = *(char*)(row_ptr + i);

      printf("%c", (oneChar >= CHAR_LOWER && oneChar <= CHAR_UPPER) ? oneChar : '.');

      if (i == 7) {
        printf(" ");
      }

    }

    buffer_size = (buffer_size > ROW_LIMIT ? buffer_size - ROW_LIMIT : 0);
    current_row++;

  }

  printf("\n");

}
