
undefined4 __fastcall FUN_006acb40(undefined4 *param_1)

{
  char cVar1;
  int *local_8;
  
  local_8 = (int *)*param_1;
  while( true ) {
    if (local_8 == (int *)0x0) {
      return 1;
    }
    cVar1 = (**(code **)(*local_8 + 4))();
    if (cVar1 == '\0') break;
    local_8 = (int *)local_8[1];
  }
  return 0;
}

