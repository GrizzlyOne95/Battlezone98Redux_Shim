
int __thiscall FUN_006c9f60(int param_1,int param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  int local_10;
  int local_8;
  
  local_8 = 0;
  if ((*(int *)(param_2 + 0x10) != 0) || (param_2 == *(int *)(param_1 + 8))) {
    while( true ) {
      if (local_8 == param_4) {
        local_10 = 0;
      }
      else {
        local_10 = get();
      }
      if (local_10 == 0) break;
      FUN_006d8cf0(0x3e3);
      FUN_006c8fb0();
      FUN_006c9000(local_10);
      local_8 = local_8 + 1;
    }
    cVar1 = FUN_004c85a0();
    if (cVar1 != '\0') {
      FUN_006ce9d0(param_2);
    }
  }
  return local_8;
}

