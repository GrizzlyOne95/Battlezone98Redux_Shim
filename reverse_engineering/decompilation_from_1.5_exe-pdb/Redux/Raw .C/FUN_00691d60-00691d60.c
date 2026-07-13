
undefined4 FUN_00691d60(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 local_8;
  
  local_8 = 0;
  iVar1 = FUN_00690950(param_1,param_3,param_4,*(uint *)(param_2 + 0x24) >> 0x12 & 0xf,
                       *(uint *)(param_2 + 0x24) >> 0x16 & 0xf);
  if (iVar1 == 0) {
    iVar1 = FUN_00434910(param_2,param_3,param_4);
    if (iVar1 != 0) {
      local_8 = 1;
    }
  }
  return local_8;
}

