
void __fastcall FUN_007cf7b0(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_008628b6;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = cUI_TextEntry::vftable;
  local_8 = 1;
  if (DAT_009456c8 != (code *)0x0) {
    (*DAT_009456c8)(param_1,0,uVar1);
  }
  local_8 = local_8 & 0xffffff00;
  ~basic_string<>();
  local_8 = 0xffffffff;
  FUN_007cc560();
  ExceptionList = local_10;
  return;
}

