
undefined4 FUN_0043f8e0(undefined4 param_1)

{
  int iVar1;
  uint local_c;
  int *local_8;
  
  local_8 = (int *)FUN_0043f2a0(param_1);
  if (((local_8 != (int *)0x0) &&
      (iVar1 = (**(code **)(*local_8 + 0x24))(local_8,&local_c), iVar1 == 0)) &&
     ((local_c & 1) != 0)) {
    return 1;
  }
  return 0;
}

