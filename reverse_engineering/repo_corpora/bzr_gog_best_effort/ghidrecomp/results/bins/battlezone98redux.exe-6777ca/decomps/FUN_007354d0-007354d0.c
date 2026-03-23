
void FUN_007354d0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined4 local_8;
  
  cVar1 = __Current_set(param_2);
  if (cVar1 == '\0') {
    FUN_006f2230(&stack0x00000014);
    FUN_006f05d0(param_2);
  }
  FUN_006f2230(&stack0x00000014);
  FUN_00734200(&stack0x0000000c);
  local_8 = FUN_007365d0(param_1,param_2);
  FUN_006d76c0(param_2,&local_8);
  FUN_006d76e0(param_2,local_c);
  FUN_006d7700(param_2,local_10);
  return;
}

