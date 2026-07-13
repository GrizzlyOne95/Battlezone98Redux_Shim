
void __fastcall FUN_00599580(int param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c0a8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if ((((*(int *)(param_1 + 0xa8) != 0) && (*(int *)(param_1 + 0xb4) <= DAT_009175a0)) &&
      (DAT_009175a0 < *(int *)(param_1 + 0xbc))) &&
     ((*(int *)(param_1 + 0xb8) <= DAT_009175a4 && (DAT_009175a4 < *(int *)(param_1 + 0xc0))))) {
    FUN_00623ff0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
    FUN_00593df0(*(undefined4 *)(param_1 + 0xa8));
    local_8 = 0;
    FUN_005940d0();
    FUN_00623eb0();
    local_8 = 0xffffffff;
    FUN_00593f30();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

