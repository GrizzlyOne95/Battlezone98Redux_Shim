
undefined4 FUN_00723810(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined1 auStack_54 [4];
  undefined4 uStack_50;
  undefined1 *puStack_4c;
  undefined1 *puStack_48;
  undefined4 uStack_44;
  undefined1 *puStack_40;
  uint uStack_3c;
  undefined1 local_38 [4];
  undefined4 local_34;
  undefined1 *local_30;
  undefined4 local_2c;
  undefined1 *local_28;
  undefined1 local_24 [4];
  uint local_20;
  undefined4 local_1c;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00858dc8;
  local_10 = ExceptionList;
  uStack_3c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  puStack_40 = local_24;
  uStack_44 = 0x72384b;
  puVar1 = (undefined4 *)FID_conflict_begin();
  puStack_40 = (undefined1 *)*puVar1;
  uStack_44 = param_2;
  puStack_48 = (undefined1 *)0x72385d;
  local_18 = puStack_40;
  local_20 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             _Pdif();
  local_28 = (undefined1 *)&puStack_48;
  puStack_4c = &stack0x00000018;
  uStack_50 = 0x723874;
  local_2c = FUN_004bbb20();
  local_8._0_1_ = 2;
  local_30 = auStack_54;
  local_1c = local_2c;
  local_34 = FUN_004bbb20(&stack0x0000000c);
  local_8._0_1_ = 1;
  FUN_007289d0(param_2,param_2);
  puStack_40 = (undefined1 *)local_20;
  uStack_44 = param_1;
  puStack_48 = local_38;
  puStack_4c = (undefined1 *)0x7238bd;
  FID_conflict_begin();
  puStack_48 = (undefined1 *)0x7238c4;
  FID_conflict_operator_();
  local_8 = (uint)local_8._1_3_ << 8;
  puStack_40 = (undefined1 *)0x7238d0;
  FUN_004bb3b0();
  local_8 = 0xffffffff;
  puStack_40 = (undefined1 *)0x7238df;
  FUN_004bb3b0();
  ExceptionList = local_10;
  return param_1;
}

