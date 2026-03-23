
void __fastcall FUN_006e4940(int param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085427b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_006e62f0(param_1 + 4);
  local_8 = 0xffffffff;
  FUN_006ca8c0(uVar1);
  ExceptionList = local_10;
  return;
}

