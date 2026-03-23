
int __fastcall FUN_006b7350(int param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00850c53;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  basic_string<>(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  FUN_006ca5f0();
  local_8 = CONCAT31(local_8._1_3_,1);
  *(undefined4 *)(param_1 + 0x20) = 0;
  basic_string<>();
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined **)(param_1 + 0x40) = &DAT_01e84800;
  *(undefined4 *)(param_1 + 0x44) = 0;
  ExceptionList = local_10;
  return param_1;
}

