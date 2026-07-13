
void __fastcall FUN_0078c190(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085e6c8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = cUI_Loading::vftable;
  local_8 = 0;
  FUN_007d45b0(*(undefined1 *)(param_1 + 0x55),*(undefined1 *)((int)param_1 + 0x155),
               *(undefined1 *)((int)param_1 + 0x156),uVar1);
  local_8 = 0xffffffff;
  FUN_007d1eb0();
  ExceptionList = local_10;
  return;
}

