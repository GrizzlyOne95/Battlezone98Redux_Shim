
void FUN_006cc7d0(undefined4 param_1)

{
  undefined4 in_stack_0000006c;
  undefined4 in_stack_0000007c;
  undefined1 auStack_e0 [92];
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined1 auStack_7c [4];
  undefined4 uStack_78;
  undefined1 *puStack_74;
  undefined4 uStack_70;
  undefined4 *puStack_6c;
  undefined4 uStack_68;
  undefined *puStack_64;
  uint uStack_60;
  undefined1 *local_5c;
  undefined1 *local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined1 *local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 *local_30;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00852b60;
  local_10 = ExceptionList;
  uStack_60 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  puStack_64 = (undefined *)in_stack_0000007c;
  local_5c = (undefined1 *)&uStack_70;
  puStack_74 = &stack0x00000070;
  uStack_78 = 0x6cc81a;
  local_14 = uStack_60;
  local_44 = FUN_006cd330();
  local_8._0_1_ = 2;
  local_58 = auStack_7c;
  uStack_80 = in_stack_0000006c;
  uStack_84 = 0x6cc838;
  local_40 = local_44;
  local_50 = FUN_006cd330();
  local_8._0_1_ = 3;
  local_48 = auStack_e0;
  local_34 = local_50;
  local_4c = FUN_006cd350(&stack0x00000008);
  local_8._0_1_ = 1;
  local_54 = FUN_006d0e30(param_1);
  local_8._0_1_ = 4;
  *local_30 = boost::date_time::
              time_facet<class_boost::posix_time::ptime,char,class_std::ostreambuf_iterator<char,struct_std::char_traits<char>_>_>
              ::vftable;
  puStack_64 = PTR_DAT_008fe82c;
  uStack_68 = 0x6cc888;
  uStack_68 = basic_string<>();
  local_8._0_1_ = 5;
  puStack_64 = PTR_s__O__M__S_F_008fe830;
  puStack_6c = local_30 + 0x3f;
  uStack_70 = 0x6cc8ae;
  local_3c = uStack_68;
  local_38 = uStack_68;
  FUN_0045f170();
  local_8._0_1_ = 4;
  puStack_64 = (undefined *)0x6cc8bd;
  ~basic_string<>();
  local_8 = (uint)local_8._1_3_ << 8;
  puStack_64 = (undefined *)0x6cc8c9;
  CCommandManager::ClearAllCmdImages((CCommandManager *)&stack0x00000008);
  local_8 = 0xffffffff;
  puStack_64 = (undefined *)0x6cc8d8;
  FUN_006c3560();
  ExceptionList = local_10;
  uStack_60 = 0x6cc8f0;
  FUN_0083e885();
  return;
}

