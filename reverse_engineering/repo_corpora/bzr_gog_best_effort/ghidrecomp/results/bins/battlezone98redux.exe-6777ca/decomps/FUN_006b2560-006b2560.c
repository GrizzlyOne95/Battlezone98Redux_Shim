
void __fastcall FUN_006b2560(runtime_error *param_1)

{
  uint uVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b778;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           basic_string<>("Year is out of valid range: 1400..10000");
  local_8 = 0;
  std::runtime_error::runtime_error(param_1,pbVar2);
  local_8 = 0xffffffff;
  ~basic_string<>(uVar1);
  *(undefined ***)param_1 = boost::gregorian::bad_year::vftable;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

