
undefined4 * __thiscall
FUN_0048f940(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

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
  *param_1 = CannonClass::vftable;
  FUN_00589430(param_1 + 8);
  local_8._0_1_ = 1;
  FUN_00589800(0x6dbf0bc4,0xd9356908,param_1 + 0x20,*(undefined4 *)(param_2 + 0x80));
  FUN_005896c0(0x6dbf0bc4,0x9260ea63,param_1 + 0x21,*(undefined4 *)(param_2 + 0x84));
  FUN_00589800(0x6dbf0bc4,0xd76f37db,param_1 + 0x22,*(undefined4 *)(param_2 + 0x88));
  FUN_00589800(0x6dbf0bc4,0x22c3372e,param_1 + 0x23,*(undefined4 *)(param_2 + 0x8c));
  FUN_00589800(0x6dbf0bc4,0x55974c81,param_1 + 0x24,*(undefined4 *)(param_2 + 0x90));
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00589530();
  ExceptionList = local_10;
  return param_1;
}

