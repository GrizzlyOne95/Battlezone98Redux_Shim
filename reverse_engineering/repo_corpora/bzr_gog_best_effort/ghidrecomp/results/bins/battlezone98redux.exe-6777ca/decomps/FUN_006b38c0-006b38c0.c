
void FUN_006b38c0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  undefined1 *puVar6;
  int local_ec [38];
  locale local_54 [8];
  uint local_4c;
  undefined1 local_48 [28];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008506b3;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_4c = 0;
  puVar6 = local_2c;
  local_14 = uVar3;
  FUN_006b3750(local_48);
  FUN_006b33d0(puVar6,param_2);
  local_8 = 0;
  iVar4 = FUN_00667170(uVar3);
  if (iVar4 == 0) {
    FUN_006ca050(2,1);
    local_8 = CONCAT31(local_8._1_3_,1);
    std::locale::classic();
    std::basic_ios<char,struct_std::char_traits<char>_>::imbue
              ((basic_ios<char,struct_std::char_traits<char>_> *)
               ((int)local_ec + *(int *)(local_ec[0] + 4)),local_54);
    FUN_00417b50();
    cVar1 = FUN_006b34f0();
    if (cVar1 == '\0') {
      uVar5 = FUN_006d9650(local_ec,0x5b,local_2c,0x5d);
      uVar5 = FUN_00574730(uVar5);
      FUN_006d9650(uVar5);
    }
    else {
      FUN_00574730(local_ec,local_2c);
    }
    uVar2 = FUN_006b36c0();
    this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_006d9650(local_ec,0x3a);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,uVar2);
    GetPolicy(param_1);
    local_4c = local_4c | 1;
    local_8 = local_8 & 0xffffff00;
    FUN_006b3a50();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  else {
    basic_string<>();
    local_4c = local_4c | 1;
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

