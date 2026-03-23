
void FUN_0075cf00(undefined4 param_1,
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                 *param_2)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  undefined4 uVar4;
  basic_istream<char,struct_std::char_traits<char>_> local_108 [176];
  undefined1 local_58 [8];
  ushort local_50 [3];
  char local_49;
  undefined1 local_48 [28];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b0d3;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  FUN_004203f0(param_2,3,1);
  local_8 = 0;
  cVar1 = FUN_0041f890(uVar2);
  if (cVar1 == '\0') {
    basic_string<>();
    local_8._0_1_ = 1;
    pcVar3 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             operator[](param_2,0);
    if (*pcVar3 == '[') {
      std::basic_istream<char,struct_std::char_traits<char>_>::get(local_108,&local_49);
      FUN_004272a0(local_108,local_2c,0x5d);
      std::basic_istream<char,struct_std::char_traits<char>_>::get(local_108,&local_49);
      if (local_49 != ':') {
        FUN_006cb470();
        local_8 = (uint)local_8._1_3_ << 8;
        ~basic_string<>();
        local_8 = 0xffffffff;
        FUN_00417f10();
        goto LAB_0075d06f;
      }
    }
    else {
      FUN_004272a0(local_108,local_2c,0x3a);
    }
    std::basic_istream<char,struct_std::char_traits<char>_>::operator>>(local_108,local_50);
    FUN_004fbb60();
    uVar2 = (uint)local_50[0];
    uVar4 = FUN_0075a020(local_48,local_2c,local_58,uVar2);
    FUN_006cb490(uVar4,uVar2);
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  else {
    FUN_006cb470();
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
LAB_0075d06f:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

