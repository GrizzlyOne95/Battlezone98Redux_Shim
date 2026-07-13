
undefined4 __thiscall FUN_005d7690(int *param_1,int param_2)

{
  int local_8;
  
  local_8 = (**(code **)(*param_1 + 0x10))();
  while( true ) {
    if (local_8 == 0) {
      return 0;
    }
    if (param_2 == local_8) break;
    local_8 = *(int *)(local_8 + 4);
  }
  return 1;
}

