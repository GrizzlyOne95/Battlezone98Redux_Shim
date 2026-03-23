
undefined4 * __thiscall
FUN_0050c250(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084ab40;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00511720(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = MagnetMineClass::vftable;
  FUN_00589430(param_1 + 0xe);
  local_8._0_1_ = 1;
  FUN_00589800(0x24f7f5bc,0x682cd2b2,param_1 + 0x5a,*(undefined4 *)(param_2 + 0x168));
  FUN_00589800(0x24f7f5bc,0x66623dd5,param_1 + 0x5b,*(undefined4 *)(param_2 + 0x16c));
  FUN_00589800(0x24f7f5bc,0x6cf48f7f,param_1 + 0x5c,*(undefined4 *)(param_2 + 0x170));
  FUN_00589800(0x24f7f5bc,0xa9b5f7e3,param_1 + 0x5d,*(undefined4 *)(param_2 + 0x174));
  FUN_00589800(0x24f7f5bc,0x27970654,param_1 + 0x5e,*(undefined4 *)(param_2 + 0x178));
  FUN_00589800(0x24f7f5bc,0xc829c5ad,param_1 + 0x5f,*(undefined4 *)(param_2 + 0x17c));
  FUN_00589800(0x24f7f5bc,0x1703fa09,param_1 + 0x60,*(undefined4 *)(param_2 + 0x180));
  FUN_00589800(0x24f7f5bc,0x5b205972,param_1 + 0x61,*(undefined4 *)(param_2 + 0x184));
  param_1[0x5d] = ((float)param_1[0x5d] - (float)param_1[0x5c]) / (float)param_1[0x5b];
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00589530();
  ExceptionList = local_10;
  return param_1;
}

