
void FUN_0082aa10(undefined4 param_1,undefined4 param_2)

{
  void *_Dst;
  void *_Src;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844a01;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  _Dst = (void *)forward<>(0x1004,param_1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  if (_Dst != (void *)0x0) {
    _Src = (void *)FUN_00417780(param_2);
    memcpy(_Dst,_Src,0x1004);
  }
  ExceptionList = local_10;
  return;
}

