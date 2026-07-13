
facet * __thiscall FUN_006d0e30(facet *param_1,undefined4 param_2)

{
  uint in_stack_00000084;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00853123;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 2;
  std::locale::facet::facet(param_1,in_stack_00000084);
  local_8._0_1_ = 3;
  *(undefined ***)param_1 =
       boost::date_time::
       date_facet<class_boost::gregorian::date,char,class_std::ostreambuf_iterator<char,struct_std::char_traits<char>_>_>
       ::vftable;
  basic_string<>(param_2);
  local_8._0_1_ = 4;
  basic_string<>(&DAT_00896170);
  local_8._0_1_ = 5;
  basic_string<>(&DAT_00896248);
  local_8._0_1_ = 6;
  FUN_006cd350(&stack0x00000008);
  local_8._0_1_ = 7;
  FUN_006cd330(&stack0x00000078);
  local_8._0_1_ = 8;
  FUN_006cd330(&stack0x0000006c);
  local_8._0_1_ = 9;
  vector<>();
  local_8._0_1_ = 10;
  vector<>();
  local_8._0_1_ = 0xb;
  vector<>();
  local_8._0_1_ = 0xc;
  vector<>();
  local_8._0_1_ = 1;
  CCommandManager::ClearAllCmdImages((CCommandManager *)&stack0x00000008);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006c3560();
  local_8 = 0xffffffff;
  FUN_006c3560();
  ExceptionList = local_10;
  return param_1;
}

