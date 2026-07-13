
void __thiscall FUN_006699b0(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 local_50 [48];
  undefined1 local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_006678e0(local_20,param_1 + 4,param_2);
  uVar1 = FUN_0041f870(local_50);
  iVar2 = FUN_00666ce0(uVar1);
  if (iVar2 == 0) {
    ~basic_string<>();
  }
  else {
    ~basic_string<>(0);
  }
  FUN_0083e885();
  return;
}

