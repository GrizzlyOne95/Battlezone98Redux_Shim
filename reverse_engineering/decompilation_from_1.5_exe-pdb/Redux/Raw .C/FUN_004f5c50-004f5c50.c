
undefined4 * __fastcall FUN_004f5c50(undefined4 *param_1)

{
  void *pvVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a6f4;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0045ca60(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = Inst01Mission::vftable;
  pvVar1 = operator_new(0x30);
  local_8 = CONCAT31(local_8._1_3_,1);
  if (pvVar1 != (void *)0x0) {
    FUN_004f5520(param_1);
  }
  ExceptionList = local_10;
  return param_1;
}

