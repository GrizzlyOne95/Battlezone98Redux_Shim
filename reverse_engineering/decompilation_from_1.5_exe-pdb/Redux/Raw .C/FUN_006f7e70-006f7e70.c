
int FUN_006f7e70(int param_1,int param_2,int param_3,int param_4)

{
  char cVar1;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = 0;
  _Distance<>(param_1,param_2,&local_8);
  local_14 = 0;
  _Distance<>(param_3,param_4,&local_14);
  do {
    if (local_8 < local_14) {
      return param_2;
    }
    local_10 = param_1;
    local_c = param_3;
    while( true ) {
      if (local_c == param_4) {
        return param_1;
      }
      cVar1 = FUN_00708c90(local_10,local_c);
      if (cVar1 == '\0') break;
      local_10 = local_10 + 1;
      local_c = local_c + 1;
    }
    param_1 = param_1 + 1;
    local_8 = local_8 + -1;
  } while( true );
}

