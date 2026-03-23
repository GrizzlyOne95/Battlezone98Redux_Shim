
void FUN_006f8d30(void)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar4;
  ushort uVar5;
  ushort uVar6;
  undefined1 auStack_170 [160];
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined1 *local_98;
  int local_94;
  uint local_90;
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [48];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008559d2;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_90 = 0;
  local_14 = uVar2;
  FUN_00574400(3,1);
  local_8 = 0;
  cVar1 = FUN_0041f890(uVar2);
  if (cVar1 == '\0') {
    local_bc = FUN_0066e860(local_44,&DAT_008848ac,local_94 + 0x4c10);
    local_8 = 2;
    local_90 = local_90 | 2;
    local_b4 = local_bc;
    local_9c = local_bc;
  }
  else {
    local_c0 = basic_string<>(&DAT_008a1ad8);
    local_8 = CONCAT31(local_8._1_3_,1);
    local_90 = local_90 | 1;
    local_ac = local_c0;
    local_9c = local_c0;
  }
  local_d0 = local_9c;
  cVar1 = FUN_0041f890(uVar2);
  if (cVar1 == '\0') {
    local_b0 = FUN_0066e860(local_5c,&DAT_008848ac,local_94 + 0x4bf4);
    local_8 = 4;
    local_90 = local_90 | 8;
    local_a4 = local_b0;
    local_a0 = local_b0;
  }
  else {
    local_cc = basic_string<>(&DAT_008a1ad8);
    local_8 = 3;
    local_90 = local_90 | 4;
    local_c4 = local_cc;
    local_a0 = local_cc;
  }
  local_b8 = local_a0;
  if (&stack0x00000000 == (undefined1 *)0x180) {
    local_98 = (undefined1 *)0x0;
  }
  else {
    local_98 = auStack_170;
  }
  uVar6 = *(ushort *)(local_94 + 0x4c0c);
  uVar5 = *(ushort *)(local_94 + 0x4bf0);
  uVar3 = FUN_004bc590(local_98,"Disconnect ","close local:[",uVar5,local_a0,"] remote:[",uVar6,
                       local_d0,&DAT_00871538);
  pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar3);
  pbVar4 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,uVar5);
  uVar3 = FUN_00574730(pbVar4);
  pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar3);
  pbVar4 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,uVar6);
  uVar3 = FUN_00574730(pbVar4);
  FUN_004bc590(uVar3);
  local_8 = 3;
  if ((local_90 & 8) != 0) {
    local_90 = local_90 & 0xfffffff7;
    ~basic_string<>();
  }
  local_8 = 2;
  if ((local_90 & 4) != 0) {
    local_90 = local_90 & 0xfffffffb;
    ~basic_string<>();
  }
  local_8 = 1;
  if ((local_90 & 2) != 0) {
    local_90 = local_90 & 0xfffffffd;
    ~basic_string<>();
  }
  local_8 = 0;
  if ((local_90 & 1) != 0) {
    local_90 = local_90 & 0xfffffffe;
    ~basic_string<>();
  }
  local_c8 = GetPolicy(local_74);
  local_8._0_1_ = 5;
  local_a8 = local_c8;
  FUN_006d4480(2,local_c8);
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

