
void FUN_007470b0(undefined4 param_1,char param_2)

{
  char cVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  code *pcVar3;
  undefined1 local_180 [4];
  undefined4 local_17c;
  undefined4 local_178;
  int local_174;
  undefined1 local_170 [4];
  int local_16c;
  int local_168;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b85b;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  cVar1 = FUN_0073a900(local_14);
  if (cVar1 != '\0') {
    FUN_0042d8c0(local_170);
    FID_conflict_begin(local_180);
    while (cVar1 = FUN_00420f10(local_180), cVar1 != '\0') {
      local_174 = FUN_0042de50();
      cVar1 = FUN_0056f780(local_174 + 0x10);
      if (cVar1 != '\0') goto LAB_007472af;
      FUN_0042da80();
    }
    if (param_2 != '\0') {
      local_17c = FUN_0073cc40();
      local_8 = 0;
      local_178 = local_17c;
      FUN_00747db0(local_17c);
      local_8 = 0xffffffff;
      FUN_0073cdf0();
      local_16c = FUN_0045e220();
      *(undefined4 *)(local_16c + 0x10) = *(undefined4 *)(local_168 + 0x28);
      *(undefined4 *)(local_16c + 0x14) = *(undefined4 *)(local_168 + 0x2c);
      *(undefined4 *)(local_16c + 0x18) = *(undefined4 *)(local_168 + 0x30);
      *(undefined4 *)(local_16c + 0x1c) = *(undefined4 *)(local_168 + 0x34);
      FUN_00743f40(local_16c,0);
      *(undefined1 *)(local_168 + 0x21) = *(undefined1 *)(local_16c + 0xb0);
      FUN_00742900(local_16c);
      pcVar3 = FUN_004bc8c0;
      FUN_0081e820("Added lobby : ",local_16c + 0x68,&DAT_00896ce8,local_16c + 0x10);
      uVar2 = FUN_0081e660();
      uVar2 = FUN_004bc590(uVar2);
      uVar2 = FUN_00574730(uVar2);
      uVar2 = FUN_004bc590(uVar2);
      this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0073ba70(uVar2);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,pcVar3);
    }
  }
LAB_007472af:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

