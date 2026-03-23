
void __thiscall FUN_005920f0(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  uint uStack_2c;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084bfb0;
  local_10 = ExceptionList;
  uStack_2c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_2c;
  ExceptionList = &local_10;
  uVar1 = FUN_0046b240();
  if (param_2 < uVar1) {
    iVar2 = FUN_0046b240();
    FUN_00592600(iVar2 - param_2);
  }
  else {
    uVar1 = FUN_0046b240();
    if (uVar1 < param_2) {
      Getal(&local_15);
      iVar2 = FUN_0046b240();
      FUN_00592670(param_2 - iVar2);
      local_8 = 0;
      iVar2 = FUN_0046b240(&local_15);
      FUN_00592dd0(*(undefined4 *)(param_1 + 4),param_2 - iVar2);
      FUN_005921b9();
      return;
    }
  }
  ExceptionList = local_10;
  return;
}

