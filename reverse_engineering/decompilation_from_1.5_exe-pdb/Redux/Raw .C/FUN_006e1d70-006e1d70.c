
void FUN_006e1d70(undefined4 param_1)

{
  undefined1 auStack_e0 [96];
  undefined4 uStack_80;
  undefined1 auStack_7c [8];
  undefined4 uStack_74;
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
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00854030;
  local_10 = ExceptionList;
  uStack_60 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  puStack_64 = (undefined *)param_1;
  local_5c = (undefined1 *)&uStack_70;
  uStack_74 = 0x6e1dac;
  local_14 = uStack_60;
  local_44 = FUN_006ccb70();
  local_8 = 0;
  local_58 = auStack_7c;
  uStack_80 = 0x6e1dc9;
  local_40 = local_44;
  local_50 = FUN_006ccef0();
  local_8 = CONCAT31(local_8._1_3_,1);
  local_48 = auStack_e0;
  local_34 = local_50;
  local_4c = FUN_006cce50(1,&DAT_008961b8,&DAT_00896190,&DAT_00896290,&DAT_008961bc);
  local_8 = 0xffffffff;
  local_54 = FUN_006d0e30(PTR_s__Y__b__d__H__M__S_F__z_008fe848);
  local_8 = 2;
  *local_30 = boost::date_time::
              time_facet<class_boost::posix_time::ptime,char,class_std::ostreambuf_iterator<char,struct_std::char_traits<char>_>_>
              ::vftable;
  puStack_64 = PTR_DAT_008fe82c;
  uStack_68 = 0x6e1e33;
  uStack_68 = basic_string<>();
  local_8._0_1_ = 3;
  puStack_64 = PTR_s__O__M__S_F_008fe830;
  puStack_6c = local_30 + 0x3f;
  uStack_70 = 0x6e1e59;
  local_3c = uStack_68;
  local_38 = uStack_68;
  FUN_0045f170();
  local_8 = CONCAT31(local_8._1_3_,2);
  puStack_64 = (undefined *)0x6e1e68;
  ~basic_string<>();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  uStack_60 = 0x6e1e87;
  FUN_0083e885();
  return;
}

