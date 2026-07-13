
void __fastcall FUN_007c2330(undefined4 *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085e6c8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = cUI_Alert::vftable;
  local_8 = 0;
  uVar2 = FUN_0081e820("deleting uiAlert Object %s\n",param_1 + 8,uVar1);
  FUN_0081e710(uVar2);
  param_1[0x52] = 0;
  param_1[0x53] = 0;
  local_8 = 0xffffffff;
  FUN_007d1eb0();
  ExceptionList = local_10;
  return;
}

