
void FUN_0082f4cb(int param_1,code *param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_50;
  undefined1 local_4c [64];
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_c = 0;
  local_50 = *(undefined4 *)(param_1 + 0x70);
  *(undefined4 **)(param_1 + 0x70) = &local_50;
  iVar1 = setjmp3(local_4c,0);
  if (iVar1 == 0) {
    (*param_2)(param_1,param_3);
  }
  *(undefined4 *)(param_1 + 0x70) = local_50;
  FUN_0083e885();
  return;
}

