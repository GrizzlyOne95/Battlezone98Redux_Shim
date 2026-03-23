
int * FUN_0042aad0(int *param_1,
                  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_2)

{
  char cVar1;
  uint _FileHandle;
  basic_streambuf<char,struct_std::char_traits<char>_> *this;
  uint uVar2;
  uint uVar3;
  int *piVar4;
  undefined4 local_38;
  int local_34;
  int local_30;
  basic_streambuf<char,struct_std::char_traits<char>_> *local_2c;
  int local_28;
  basic_streambuf<char,struct_std::char_traits<char>_> *local_24;
  int local_20;
  uint local_1c;
  char local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845668;
  local_10 = ExceptionList;
  _FileHandle = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = &stack0xffffffa8;
  ExceptionList = &local_10;
  local_1c = 0;
  local_15 = '\0';
  FUN_0041f920(param_1,1);
  local_8 = 0;
  cVar1 = FUN_0041f990();
  if (cVar1 == '\0') {
    if (local_15 == '\0') {
      local_1c = local_1c | 2;
    }
    std::basic_ios<char,struct_std::char_traits<char>_>::setstate
              ((basic_ios<char,struct_std::char_traits<char>_> *)
               ((int)param_1 + *(int *)(*param_1 + 4)),local_1c,false);
    local_8 = 0xffffffff;
    FUN_00417c30();
    ExceptionList = local_10;
    return param_1;
  }
  local_8 = CONCAT31(local_8._1_3_,1);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::erase
            (param_2,0);
  local_38 = FUN_00417ab0(&stack0x0000000c);
  local_24 = std::basic_ios<char,struct_std::char_traits<char>_>::rdbuf
                       ((basic_ios<char,struct_std::char_traits<char>_> *)
                        ((int)param_1 + *(int *)(*param_1 + 4)));
  local_28 = std::basic_streambuf<char,struct_std::char_traits<char>_>::sgetc(local_24);
  local_20 = local_28;
  do {
    local_34 = eof(_FileHandle);
    cVar1 = eq_int_type(&local_34,&local_20);
    if (cVar1 != '\0') {
      local_1c = local_1c | 1;
LAB_0042ac4b:
      piVar4 = (int *)FUN_0042ac68();
      return piVar4;
    }
    cVar1 = eq_int_type(&local_20,&local_38);
    if (cVar1 != '\0') {
      local_15 = '\x01';
      this = std::basic_ios<char,struct_std::char_traits<char>_>::rdbuf
                       ((basic_ios<char,struct_std::char_traits<char>_> *)
                        ((int)param_1 + *(int *)(*param_1 + 4)));
      std::basic_streambuf<char,struct_std::char_traits<char>_>::sbumpc(this);
      goto LAB_0042ac4b;
    }
    uVar2 = FUN_004170c0();
    uVar3 = FID_conflict_max_size();
    if (uVar3 <= uVar2) {
      local_1c = local_1c | 2;
      goto LAB_0042ac4b;
    }
    cVar1 = FUN_00417aa0(&local_20);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
              (param_2,cVar1);
    local_15 = '\x01';
    local_2c = std::basic_ios<char,struct_std::char_traits<char>_>::rdbuf
                         ((basic_ios<char,struct_std::char_traits<char>_> *)
                          ((int)param_1 + *(int *)(*param_1 + 4)));
    local_30 = std::basic_streambuf<char,struct_std::char_traits<char>_>::snextc(local_2c);
    local_20 = local_30;
  } while( true );
}

