
bool FUN_00428ca0(char *param_1,char *param_2)

{
  char cVar1;
  char cVar2;
  
  for (; (*param_1 != '\0' && (*param_2 != '\0')); param_2 = param_2 + 1) {
    cVar1 = FUN_00429d60(*param_1);
    cVar2 = FUN_00429d60(*param_2);
    if ((int)cVar1 != (int)cVar2) {
      return (int)cVar1 - (int)cVar2 < 0;
    }
    param_1 = param_1 + 1;
  }
  return *param_2 != '\0';
}

