
void __thiscall FUN_006b2e50(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  undefined1 local_108 [256];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar2 = 0;
  iVar1 = FUN_006afba0(2,param_1,local_108,0x100,0,param_3);
  if (iVar1 == 0) {
    basic_string<>();
  }
  else {
    basic_string<>(iVar1);
  }
  FUN_0083e885(param_1,iVar1,uVar2 | 1);
  return;
}

