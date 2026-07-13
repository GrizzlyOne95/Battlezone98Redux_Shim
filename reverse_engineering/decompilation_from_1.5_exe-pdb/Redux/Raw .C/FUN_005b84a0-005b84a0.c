
void __fastcall FUN_005b84a0(undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00849598;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = ScavGotoScrap::vftable;
  local_8 = 0;
  iVar2 = FUN_00462630(param_1[5],uVar1);
  if (iVar2 != 0) {
    uVar3 = (**(code **)(*(int *)(param_1[4] + 0x18) + 4))();
    FUN_005a38a0(uVar3);
  }
  local_8 = 0xffffffff;
  FUN_0049da90();
  ExceptionList = local_10;
  return;
}

