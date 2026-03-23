
int __fastcall FUN_006cc3b0(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  void *_Dst;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00852b0b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 8));
  local_8 = 0;
  uVar2 = FUN_006d0d10(uVar1);
  _Dst = (void *)forward<>(1,uVar2);
  if (_Dst != (void *)0x0) {
    memset(_Dst,0,1);
  }
  FUN_0045ba10(0);
  ExceptionList = local_10;
  return param_1;
}

