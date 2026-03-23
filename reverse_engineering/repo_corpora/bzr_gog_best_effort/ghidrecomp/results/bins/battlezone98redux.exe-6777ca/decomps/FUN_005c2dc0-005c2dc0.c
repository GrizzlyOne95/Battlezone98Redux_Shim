
undefined4 * __thiscall
FUN_005c2dc0(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c680;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_004f0130(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = ScavengerClass::vftable;
  FUN_00589430(param_1 + 0xe);
  local_8._0_1_ = 1;
  FUN_00589760(0x3b47476d,0x5424e,param_1 + 0x17c,*(undefined4 *)(param_2 + 0x5f0));
  FUN_0047b6c0(0x3b47476d,0xc7620108,param_1 + 0x17d,param_2 + 0x5f4);
  FUN_0047b6c0(0x3b47476d,0x41e5b62b,param_1 + 0x181,param_2 + 0x604);
  FUN_0047b6c0(0x3b47476d,0x43d74028,param_1 + 0x185,param_2 + 0x614);
  FUN_0047b6c0(0x3b47476d,0xcf941f93,param_1 + 0x189,param_2 + 0x624);
  FUN_0047b6c0(0x3b47476d,0xcc359f08,param_1 + 0x18d,param_2 + 0x634);
  if (*(char *)(param_1 + 0x33) == 'b') {
    local_11 = 0x61;
  }
  else if (*(char *)(param_1 + 0x33) == 'c') {
    local_11 = 0x73;
  }
  else {
    local_11 = 0;
  }
  FUN_005c2d60(param_1 + 0x181,*(undefined1 *)(param_1 + 0x33),local_11,0x31);
  FUN_005c2d60(param_1 + 0x185,*(undefined1 *)(param_1 + 0x33),local_11,0x35);
  FUN_005c2d60(param_1 + 0x189,*(undefined1 *)(param_1 + 0x33),local_11,0x68);
  FUN_005c2d60(param_1 + 0x18d,*(undefined1 *)(param_1 + 0x33),local_11,0x69);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00589530();
  ExceptionList = local_10;
  return param_1;
}

