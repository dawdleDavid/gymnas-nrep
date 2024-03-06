
#include <stdint.h>


uint64_t string_lenght(const char* string){
  uint64_t len=0;
  while(string[len] != '\0'){
    len++;
  }
  return len;
}
uint8_t string_compare(const char* a, const char* b){
  if(string_lenght(a) > string_lenght(b)){
    return (string_lenght(a) - string_lenght(b));
  }else if(string_lenght(a) < string_lenght(b)){
    return (string_lenght(b) - string_lenght(a));
  }
  // test if strings are equal in lenght
  for(uint64_t i = 0; i <= string_lenght(b); i++){
    if(a[i] != b[i]){
      return 1;
    }
  }
  return 0;
}
