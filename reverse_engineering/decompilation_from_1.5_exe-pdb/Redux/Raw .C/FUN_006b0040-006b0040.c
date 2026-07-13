
void __fastcall FUN_006b0040(int *param_1)

{
  undefined1 local_20 [8];
  int *local_18;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00850328;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  local_18 = param_1;
  if (*param_1 != -1) {
    FUN_004fbb60(DAT_008e7000 ^ (uint)&stack0xfffffffc);
    local_11 = 0;
    FUN_006ae9c0(*local_18,&local_11,1,local_20);
  }
  local_8 = 0xffffffff;
  FUN_00417c60();
  ExceptionList = local_10;
  return;
}

