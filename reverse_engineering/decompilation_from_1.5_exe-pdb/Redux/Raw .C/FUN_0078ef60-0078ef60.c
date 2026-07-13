
void __thiscall FUN_0078ef60(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined1 local_34 [40];
  code *local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (*(int *)(param_1 + 0x160) != 0) {
    FUN_0043aaa0(*(undefined4 *)(param_1 + 0x160));
  }
  FUN_0043a990(local_34);
  local_c = FUN_0078ed40;
  uVar1 = FUN_0043aa30(param_2,0,local_34,0);
  *(undefined4 *)(param_1 + 0x160) = uVar1;
  FUN_0043a170(0);
  FUN_0083e885();
  return;
}

