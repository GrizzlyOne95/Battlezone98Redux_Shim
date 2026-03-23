
char * FUN_00770e40(char *param_1,char *param_2)

{
  char cVar1;
  int local_8;
  
  while( true ) {
    if (param_1 == param_2) {
      return param_1;
    }
    local_8 = (int)*param_1;
    cVar1 = FUN_00771520(&local_8);
    if (cVar1 != '\0') break;
    param_1 = param_1 + 1;
  }
  return param_1;
}

