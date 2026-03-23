
void FUN_00721110(char *param_1,char *param_2)

{
  uint uStack_2c;
  uint local_1c;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00858cf0;
  local_10 = ExceptionList;
  uStack_2c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_2c;
  ExceptionList = &local_10;
  local_1c = 0;
  _Distance<>(param_1,param_2,&local_1c);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::reserve
            (local_18,local_1c);
  local_8 = 0;
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
              (local_18,1,*param_1);
  }
  FUN_007211b0();
  return;
}

