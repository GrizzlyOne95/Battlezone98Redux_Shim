
void __fastcall FUN_007ca720(undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_008624e4;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = cUI_Selectlist::vftable;
  local_8 = 2;
  for (local_18 = 0; iVar2 = size(uVar1), local_18 < iVar2; local_18 = local_18 + 1) {
    piVar3 = (int *)FUN_004200d0(local_18);
    if ((undefined4 *)*piVar3 != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)*piVar3)(1);
    }
  }
  local_8._0_1_ = 1;
  FUN_007cb760();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_0041fe20();
  local_8 = 0xffffffff;
  FUN_007d1eb0();
  ExceptionList = local_10;
  return;
}

