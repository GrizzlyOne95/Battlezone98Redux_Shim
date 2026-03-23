
void FUN_0062f330(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined1 local_5c [72];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_0062bf70(local_5c,param_2);
  local_14 = *(undefined4 *)(iVar1 + 0x18);
  local_10 = *(undefined4 *)(iVar1 + 0x1c);
  local_c = *(undefined4 *)(iVar1 + 0x20);
  FUN_008245f0(param_1,param_2,&local_14,param_3 + 0x6c,param_3 + 0x54);
  FUN_0083e885();
  return;
}

