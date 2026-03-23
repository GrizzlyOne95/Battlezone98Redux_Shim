
undefined4
FUN_0080b950(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  char cVar1;
  int iVar2;
  undefined1 local_20 [12];
  undefined4 local_14;
  undefined4 local_c;
  undefined1 local_5;
  
  iVar2 = FUN_007df2f0();
  if (iVar2 != 0) {
    FUN_007fd410(param_1,param_2,param_4);
    local_14 = FUN_00417780(param_5);
    local_c = FUN_00417780(local_14);
    FUN_007ef2f0(local_c);
    allocator<>(param_4);
    cVar1 = FUN_007ff0b0(param_1,param_2,local_20,&local_5);
    if (cVar1 != '\0') {
      FUN_007ff1d0(param_5,local_c);
      return 1;
    }
    FUN_007ff1f0(param_5,local_c);
  }
  return 0;
}

