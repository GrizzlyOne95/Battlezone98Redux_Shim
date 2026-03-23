
void FUN_008289d0(void)

{
  char cVar1;
  wchar_t *pwVar2;
  undefined4 uVar3;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  uint local_d4;
  undefined1 local_d0 [8];
  undefined1 local_c8 [28];
  undefined1 local_ac [28];
  undefined1 local_90 [28];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
  local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008651c4;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_d4 = 0;
  vector<>(local_14);
  local_8 = 0;
  basic_string<>(&DAT_02cf3000);
  local_8 = CONCAT31(local_8._1_3_,1);
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    pwVar2 = std::
             basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::
             back(local_2c);
    if ((char)*pwVar2 != '/') {
      pwVar2 = std::
               basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
               ::back(local_2c);
      if ((char)*pwVar2 != '\\') {
        local_e0 = FUN_0048b7d0(local_44,local_2c,&DAT_00871328);
        FUN_0045e0f0(local_e0);
        ~basic_string<>();
      }
    }
    local_f8 = FUN_004170c0();
    local_f0 = FUN_00829fb0(local_c8,local_2c,&local_f8);
    local_8._0_1_ = 2;
    local_dc = local_f0;
    FUN_00829810(local_f0);
    local_8 = CONCAT31(local_8._1_3_,1);
    FUN_00430320();
  }
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             local_2c,(char *)&DAT_02cecf80);
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    pwVar2 = std::
             basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::
             back(local_2c);
    if ((char)*pwVar2 != '/') {
      pwVar2 = std::
               basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
               ::back(local_2c);
      if ((char)*pwVar2 != '\\') {
        local_e4 = FUN_0048b7d0(local_5c,local_2c,&DAT_00871328);
        FUN_0045e0f0(local_e4);
        ~basic_string<>();
      }
    }
    local_ec = FUN_004170c0();
    local_f4 = FUN_00829fb0(local_ac,local_2c,&local_ec);
    local_8._0_1_ = 3;
    FUN_00829810(local_f4);
    local_8 = CONCAT31(local_8._1_3_,1);
    FUN_00430320();
  }
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             local_2c,&DAT_02cf0000);
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    pwVar2 = std::
             basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::
             back(local_2c);
    if ((char)*pwVar2 != '/') {
      pwVar2 = std::
               basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
               ::back(local_2c);
      if ((char)*pwVar2 != '\\') {
        uVar3 = FUN_0048b7d0(local_74,local_2c,&DAT_00871328);
        FUN_0045e0f0(uVar3);
        ~basic_string<>();
      }
    }
    local_d8 = FUN_004170c0();
    local_e8 = FUN_00829fb0(local_90,local_2c,&local_d8);
    local_8._0_1_ = 4;
    FUN_00829810(local_e8);
    local_8 = CONCAT31(local_8._1_3_,1);
    FUN_00430320();
  }
  FUN_00829790(local_d0);
  local_d4 = local_d4 | 1;
  local_8 = local_8 & 0xffffff00;
  ~basic_string<>();
  local_8 = 0xffffffff;
  FUN_00829850();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

