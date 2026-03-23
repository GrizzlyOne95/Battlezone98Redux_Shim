
void FUN_006bec80(byte *param_1,uint param_2,char *param_3)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar5;
  code *pcVar6;
  basic_ostream<char,struct_std::char_traits<char>_> local_fc [160];
  undefined1 local_5c [16];
  undefined1 local_4c [8];
  undefined4 local_44;
  uint local_40;
  undefined4 local_3c;
  uint local_38;
  char local_31;
  int local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085170b;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  FUN_00574400(3,1);
  local_8 = 0;
  for (local_38 = 0; local_38 < param_2; local_38 = local_38 + 1) {
    uVar3 = (uint)*param_1;
    local_40 = uVar3;
    uVar4 = std::setw(CONCAT44(2,local_5c));
    pcVar6 = FUN_006ab840;
    pbVar5 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                       (local_fc,FUN_00574a10);
    pbVar5 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar5,pcVar6);
    pbVar5 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_006db8a0(pbVar5,uVar4);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar5,uVar3);
    param_1 = param_1 + 1;
  }
  cVar1 = FUN_0041f890(uVar2);
  if (cVar1 == '\0') {
    cVar1 = FUN_0041f890(uVar2);
    if (cVar1 != '\0') goto LAB_006bed61;
  }
  else {
LAB_006bed61:
    if (*(int *)(local_30 + 4) == 0) {
      local_3c = 1;
      goto LAB_006bed7a;
    }
  }
  local_3c = 0;
LAB_006bed7a:
  local_31 = (char)local_3c;
  local_44 = GetPolicy(local_2c);
  FUN_0045e0f0(local_44);
  ~basic_string<>();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (local_30 + 0x304),param_3);
  if (local_31 != '\0') {
    cVar1 = FUN_006ab7d0();
    if (cVar1 == '\0') {
      FUN_004fbb60();
      FUN_006c35c0(local_4c);
    }
  }
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

