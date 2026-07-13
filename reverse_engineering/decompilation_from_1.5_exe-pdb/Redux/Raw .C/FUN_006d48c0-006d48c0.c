
undefined4 __fastcall FUN_006d48c0(undefined4 param_1)

{
  uint _FileHandle;
  int iVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008533f8;
  local_10 = ExceptionList;
  _FileHandle = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00843f40();
  local_8 = 0;
  iVar1 = eof(_FileHandle);
  FUN_00416430(0,iVar1);
  FUN_006b4800();
  ExceptionList = local_10;
  return param_1;
}

