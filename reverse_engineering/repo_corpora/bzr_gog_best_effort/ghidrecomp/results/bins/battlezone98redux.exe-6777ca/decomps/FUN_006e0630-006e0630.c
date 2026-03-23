
void __fastcall FUN_006e0630(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00853e16;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 1;
  ~_String_val<>(DAT_008e7000 ^ (uint)&stack0xfffffffc,param_1);
  local_8 = local_8 & 0xffffff00;
  FUN_006cd590();
  local_8 = 0xffffffff;
  FUN_006cd590();
  ExceptionList = local_10;
  return;
}

