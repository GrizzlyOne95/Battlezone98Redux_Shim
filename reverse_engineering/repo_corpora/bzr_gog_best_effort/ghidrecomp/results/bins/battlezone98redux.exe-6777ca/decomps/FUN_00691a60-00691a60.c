
void FUN_00691a60(undefined4 *param_1)

{
  int iVar1;
  undefined1 local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_006a3c40(local_58,*param_1);
  while (iVar1 = FUN_006a3c70(local_58), iVar1 != 0) {
    if (((*(uint *)(*(int *)(iVar1 + 0x14) + 0x24) >> 1 & 1) != 0) &&
       ((*(int *)(iVar1 + 0x1c) == 1 || (*(int *)(iVar1 + 0x1c) == 0)))) {
      FUN_006919a0(param_1,iVar1);
    }
  }
  FUN_0083e885();
  return;
}

