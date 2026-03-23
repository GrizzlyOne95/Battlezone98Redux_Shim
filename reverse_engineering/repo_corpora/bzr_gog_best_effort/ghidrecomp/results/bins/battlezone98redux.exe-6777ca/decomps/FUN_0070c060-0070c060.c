
int FUN_0070c060(int param_1,int param_2,undefined4 param_3)

{
  char cVar1;
  
  while (param_1 != 0) {
    cVar1 = FUN_00717280(&param_1,param_3);
    if (cVar1 == '\0') {
      param_2 = param_1;
      param_1 = FUN_006d6720(&param_1);
    }
    else {
      param_1 = FUN_006d6730(&param_1);
    }
  }
  return param_2;
}

