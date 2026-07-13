
int __fastcall FUN_006b8e60(int param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850ff3;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006b7350(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,1);
  *(undefined4 *)(param_1 + 0x60) = 0;
  FUN_006da100(param_1 + 100);
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  ExceptionList = local_10;
  return param_1;
}

