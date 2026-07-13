
undefined4 __fastcall FUN_006cb540(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008528e8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006cfbe0(0);
  local_8 = 0;
  FUN_006d08b0(0x400,"client constructor");
  ExceptionList = local_10;
  return param_1;
}

