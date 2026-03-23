
void __fastcall FUN_007d7860(int param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00862ec8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  ATL::_ATL_WIN_MODULE70::~_ATL_WIN_MODULE70((_ATL_WIN_MODULE70 *)(param_1 + 0x20));
  local_8 = 0xffffffff;
  FUN_006e4470(uVar1);
  ExceptionList = local_10;
  return;
}

