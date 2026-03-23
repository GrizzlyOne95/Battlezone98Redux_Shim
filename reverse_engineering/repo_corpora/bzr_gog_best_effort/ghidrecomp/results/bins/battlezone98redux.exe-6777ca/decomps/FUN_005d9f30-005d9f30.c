
undefined4 * __thiscall
FUN_005d9f30(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849340;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00611aa0(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = SpecialItemClass::vftable;
  FUN_00589430(param_1 + 8);
  local_8._0_1_ = 1;
  FUN_0047b6c0(0xef2ff121,0xd46356b6,param_1 + 0x21,param_2 + 0x84);
  FUN_0047b6c0(0xef2ff121,0x6a2f4e9,param_1 + 0x25,param_2 + 0x94);
  FUN_00589760(0xef2ff121,0xe4af0ab6,param_1 + 0xd,*(undefined4 *)(param_2 + 0x34));
  FUN_00589800(0xef2ff121,0x682cd2b2,param_1 + 0x20,*(undefined4 *)(param_2 + 0x80));
  FUN_00589760(0xef2ff121,0x2c5533ae,param_1 + 0x29,*(undefined4 *)(param_2 + 0xa4));
  param_1[0x20] = (float)param_1[0x20] / (float)(param_1[0x29] + 1);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00589530();
  ExceptionList = local_10;
  return param_1;
}

