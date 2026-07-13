
void FUN_00741b20(undefined4 param_1,undefined4 param_2,char param_3)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar4;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar5;
  int iVar6;
  code *pcVar7;
  undefined4 uVar8;
  undefined1 auStack_f8 [160];
  undefined1 local_58 [4];
  undefined4 local_54;
  undefined1 local_50 [4];
  undefined1 local_4c [4];
  char *local_48;
  undefined1 *local_44;
  char *local_40;
  int local_3c;
  undefined1 local_38 [4];
  undefined4 local_34;
  int *local_30;
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
  FUN_00574400(3,1);
  local_8 = 0;
  if (param_3 == '\0') {
    local_40 = " (FAILED)";
  }
  else {
    local_40 = "";
  }
  if (&stack0x00000000 == (undefined1 *)0x108) {
    local_44 = (undefined1 *)0x0;
  }
  else {
    local_44 = auStack_f8;
  }
  pcVar7 = FUN_004bc8c0;
  uVar3 = FUN_004bc590(local_44,"CNetGameLobby::OnLobbyDataUpdate called for lobby ",param_1,
                       ", member ",param_2,local_40,FUN_004bc8c0,uVar2);
  uVar3 = FUN_0073ba70(uVar3);
  uVar3 = FUN_004bc590(uVar3);
  uVar3 = FUN_0073ba70(uVar3);
  pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar3);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pcVar7);
  pbVar5 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
  FUN_0081e820();
  pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pbVar5);
  FUN_0042d8c0(local_38);
  FID_conflict_begin(local_50);
  while (cVar1 = FUN_00420f10(local_50), cVar1 != '\0') {
    uVar3 = param_1;
    FUN_0042da60(param_1);
    cVar1 = FUN_0056f780(uVar3);
    if (cVar1 != '\0') {
      if (param_3 != '\0') {
        basic_string<>("GameVersion");
        local_8._0_1_ = 1;
        iVar6 = FUN_0042da60(local_2c);
        local_48 = (char *)(**(code **)(*local_30 + 0x2c))(iVar6 + 0x10);
        local_8 = (uint)local_8._1_3_ << 8;
        ~basic_string<>();
        if ((local_48 != (char *)0x0) && (*local_48 != '\0')) {
          cVar1 = FUN_0056f780(param_2);
          if ((cVar1 == '\0') && (cVar1 = FUN_0073a900(), cVar1 != '\0')) {
            cVar1 = FUN_0056f780(param_1);
            if ((cVar1 != '\0') && (local_3c = FUN_0056f900(), local_3c != 0)) {
              FUN_00744a50(local_3c,param_2);
              FUN_007476a0();
            }
          }
          else {
            uVar8 = 0;
            uVar3 = FUN_0042de50(0);
            FUN_00743f40(uVar3,uVar8);
            FUN_007476a0();
          }
        }
        goto LAB_00741e29;
      }
      FUN_0042d8c0(&local_34);
      FID_conflict_begin(local_4c);
      goto LAB_00741d62;
    }
    FUN_0042da80();
  }
  local_8 = 0xffffffff;
  FUN_00417f10();
LAB_00741e5c:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
LAB_00741d62:
  cVar1 = FUN_00420f10(local_4c);
  if (cVar1 == '\0') goto LAB_00741e29;
  uVar3 = param_1;
  FUN_0042da60(param_1);
  cVar1 = FUN_0056f780(uVar3);
  if (cVar1 != '\0') {
    pcVar7 = FUN_004bc8c0;
    iVar6 = FUN_0042da60();
    iVar6 = FUN_0042da60(&DAT_00896ce8,iVar6 + 0x10);
    FUN_0081e820("Removing lobby : ",iVar6 + 0x68);
    uVar3 = FUN_0081e660();
    uVar3 = FUN_004bc590(uVar3);
    uVar3 = FUN_00574730(uVar3);
    uVar3 = FUN_004bc590(uVar3);
    pbVar4 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0073ba70(uVar3);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar4,pcVar7);
    local_54 = local_34;
    FUN_00747ca0(local_58,local_34);
    FUN_007476a0();
    goto LAB_00741e29;
  }
  FUN_0042da80();
  goto LAB_00741d62;
LAB_00741e29:
  local_8 = 0xffffffff;
  FUN_00417f10();
  goto LAB_00741e5c;
}

