
void __thiscall FUN_00829570(int param_1,uint param_2)

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
  puStack_c = &LAB_00865230;
  local_10 = ExceptionList;
  uStack_2c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_2c;
  ExceptionList = &local_10;
  uVar1 = FUN_00829680();
  if (param_2 < uVar1) {
    iVar2 = FUN_00829680();
    FUN_00829890(iVar2 - param_2);
  }
  else {
    uVar1 = FUN_00829680();
    if (uVar1 < param_2) {
      Getal(&local_15);
      iVar2 = FUN_00829680();
      FUN_00829a40(param_2 - iVar2);
      local_8 = 0;
      iVar2 = FUN_00829680(&local_15);
      FUN_00829ff0(*(undefined4 *)(param_1 + 4),param_2 - iVar2);
      FUN_00829639();
      return;
    }
  }
  ExceptionList = local_10;
  return;
}

