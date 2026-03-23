
void __fastcall FUN_007c33e0(undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00861ed2;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = cUI_Checklist::vftable;
  local_8 = 3;
  if ((undefined4 *)param_1[0x7c] != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)param_1[0x7c])(1,uVar1);
  }
  for (local_18 = 0; iVar2 = size(), local_18 < iVar2; local_18 = local_18 + 1) {
    puVar3 = (undefined4 *)FUN_004200d0(local_18);
    operator_delete((void *)*puVar3);
  }
  local_8._0_1_ = 2;
  FUN_0041fe20();
  local_8._0_1_ = 1;
  FUN_004499a0();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_004499a0();
  local_8 = 0xffffffff;
  FUN_007d1eb0();
  ExceptionList = local_10;
  return;
}

