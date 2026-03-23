
void FUN_0083a68b(int param_1,undefined4 param_2)

{
  bool bVar1;
  undefined1 local_38 [24];
  undefined1 local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00838ffd(param_1);
  FUN_0083b36f(param_1,local_20);
  while (*(int *)(param_1 + 0x10) == 0x2e) {
    FUN_0083a1ce(param_1,local_20);
  }
  bVar1 = *(int *)(param_1 + 0x10) == 0x3a;
  if (bVar1) {
    FUN_0083a1ce(param_1,local_20);
  }
  FUN_0083998e(param_1,local_38,bVar1,param_2);
  FUN_0083cef1(*(undefined4 *)(param_1 + 0x30),local_20,local_38);
  FUN_0083c857(*(undefined4 *)(param_1 + 0x30),param_2);
  FUN_0083e885();
  return;
}

