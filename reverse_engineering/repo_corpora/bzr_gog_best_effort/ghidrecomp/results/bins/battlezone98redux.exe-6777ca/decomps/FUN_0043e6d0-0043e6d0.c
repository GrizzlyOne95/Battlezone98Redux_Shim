
void FUN_0043e6d0(undefined4 param_1,undefined4 param_2)

{
  uint uStack_3c;
  ULONG_PTR local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined1 *local_1c;
  void *local_14;
  code *pcStack_10;
  uint local_c;
  undefined4 local_8;
  
  local_8 = 0xfffffffe;
  pcStack_10 = FUN_0083f1c9;
  local_14 = ExceptionList;
  local_c = DAT_008e7000 ^ 0x8b84f0;
  uStack_3c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1c = (undefined1 *)&uStack_3c;
  ExceptionList = &local_14;
  Sleep(10);
  local_2c = 0x1000;
  local_28 = param_2;
  local_24 = param_1;
  local_20 = 0;
  local_8 = 0;
  RaiseException(0x406d1388,0,4,&local_2c);
  ExceptionList = local_14;
  return;
}

