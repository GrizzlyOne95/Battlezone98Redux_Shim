
int __fastcall FUN_00801920(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_18 [4];
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008647eb;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = param_1;
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 4));
  local_8 = 0;
  uVar2 = FUN_006d0d10(uVar1);
  FUN_00447eb0(uVar2);
  FUN_00803ad0(local_18);
  uVar2 = FUN_006d4bb0();
  FUN_0045ba10(uVar2);
  ExceptionList = local_10;
  return local_14;
}

