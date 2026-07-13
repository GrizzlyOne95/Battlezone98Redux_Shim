
undefined1 * __fastcall FUN_00765cd0(undefined1 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085d146;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = 0;
  FUN_00766140(uVar1);
  local_8 = 0;
  FUN_007661b0(param_1,FUN_004178a0);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00766240(param_1,FUN_00765d60);
  ExceptionList = local_10;
  return param_1;
}

