
undefined4 * __thiscall
FUN_00511d20(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084acc0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_004f0130(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = MinelayerClass::vftable;
  FUN_00589430(param_1 + 0xe);
  local_8._0_1_ = 1;
  FUN_005896c0(0x21433f4d,0x230e7645,param_1 + 0x17c,*(undefined4 *)(param_2 + 0x5f0));
  FUN_00589800(0x21433f4d,0xcbd762f4,param_1 + 0x17d,*(undefined4 *)(param_2 + 0x5f4));
  FUN_00589800(0x21433f4d,0x9a6f5118,param_1 + 0x17e,*(undefined4 *)(param_2 + 0x5f8));
  cVar1 = FUN_00589800(0x21433f4d,0x24c9d62d,param_1 + 0x17f,*(undefined4 *)(param_2 + 0x5fc));
  if (cVar1 != '\0') {
    param_1[0x17f] = (float)param_1[0x17f] * 0.017453292;
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00589530();
  ExceptionList = local_10;
  return param_1;
}

