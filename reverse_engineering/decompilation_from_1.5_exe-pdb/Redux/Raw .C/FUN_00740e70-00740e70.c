
void FUN_00740e70(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar4;
  int iVar5;
  undefined4 *puVar6;
  _func_basic_ostream<char,struct_std::char_traits<char>_>_ptr_basic_ostream<char,struct_std::char_traits<char>_>_ptr
  *p_Var7;
  code *pcVar8;
  code *pcVar9;
  code *pcVar10;
  _func_basic_ostream<char,struct_std::char_traits<char>_>_ptr_basic_ostream<char,struct_std::char_traits<char>_>_ptr
  *p_Var11;
  int *piVar12;
  undefined1 auStack_2d8 [160];
  undefined1 local_238 [16];
  undefined1 local_228 [8];
  undefined1 local_220 [8];
  undefined1 local_218 [4];
  undefined1 local_214 [4];
  undefined1 local_210 [4];
  undefined1 local_20c [4];
  undefined1 local_208 [4];
  undefined4 local_204;
  undefined4 local_200;
  undefined1 local_1fc [4];
  undefined1 local_1f8 [4];
  undefined4 local_1f4;
  undefined4 local_1f0;
  undefined4 local_1ec;
  undefined4 local_1e8;
  undefined4 local_1e4;
  undefined4 local_1e0;
  undefined1 *local_1dc;
  undefined4 local_1d8 [3];
  undefined1 local_1cc [4];
  undefined4 local_1c8;
  int local_1c4;
  _func_basic_ostream<char,struct_std::char_traits<char>_>_ptr_basic_ostream<char,struct_std::char_traits<char>_>_ptr
  *local_1c0;
  int local_1bc;
  undefined4 local_1b8;
  char local_1b1;
  int *local_1b0;
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b039;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00574400(3,1);
  local_8 = 0;
  if (&stack0x00000000 == (undefined1 *)0x2e8) {
    local_1dc = (undefined1 *)0x0;
  }
  else {
    local_1dc = auStack_2d8;
  }
  pcVar10 = FUN_004bc8c0;
  pcVar9 = FUN_006ab840;
  iVar5 = param_1;
  uVar2 = std::setw(CONCAT44(8,local_238));
  pcVar8 = FUN_00574a10;
  pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)
           FUN_004bc590(local_1dc,"CNetGameLobby::OnLobbyListReceived, matching lobbies: ",
                        FUN_00574a10,uVar2);
  pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar8);
  pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_006db8a0(pbVar3);
  pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar9);
  pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,iVar5);
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar10);
  pbVar4 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
  FUN_0081e820();
  pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pbVar4);
  local_1b1 = '\0';
  FUN_00428520();
  local_8._0_1_ = 1;
  FUN_00429ce0();
  FUN_0042d8c0(&local_1c8);
  FID_conflict_begin(local_1d8);
  while (cVar1 = FUN_00420f10(local_1d8), cVar1 != '\0') {
    iVar5 = FUN_0042da60();
    FUN_00578af0(local_228,iVar5 + 0x10);
    FUN_0042da80();
  }
  for (local_1c0 = (_func_basic_ostream<char,struct_std::char_traits<char>_>_ptr_basic_ostream<char,struct_std::char_traits<char>_>_ptr
                    *)0x0; (int)local_1c0 < param_1; local_1c0 = local_1c0 + 1) {
    p_Var11 = local_1c0;
    (**(code **)(*local_1b0 + 0x74))(&local_1ec);
    basic_string<>(&DAT_00879d2c);
    local_8._0_1_ = 2;
    basic_string<>("gameSettings");
    local_8._0_1_ = 3;
    basic_string<>("GameVersion");
    local_8._0_1_ = 4;
    uVar2 = (**(code **)(*local_1b0 + 0x2c))(&local_1ec,local_5c,FUN_004bc8c0);
    uVar2 = (**(code **)(*local_1b0 + 0x2c))(&local_1ec,local_44,&DAT_00892870,uVar2);
    uVar2 = (**(code **)(*local_1b0 + 0x2c))(&local_1ec,local_2c,&DAT_00892870,uVar2);
    pcVar8 = FUN_0056f740;
    p_Var7 = local_1c0;
    FUN_0081e820("OnLobbyListReceived: Index ",local_1c0,", ID ",FUN_0056f740,&local_1ec,
                 &DAT_00892870,uVar2);
    uVar2 = FUN_0081e660();
    pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar2);
    pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,(int)p_Var7)
    ;
    pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(pbVar3);
    pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar8);
    uVar2 = FUN_0073ba70(pbVar3);
    uVar2 = FUN_004bc590(uVar2);
    uVar2 = FUN_004bc590(uVar2);
    uVar2 = FUN_004bc590(uVar2);
    uVar2 = FUN_004bc590(uVar2);
    uVar2 = FUN_004bc590(uVar2);
    pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar2);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,p_Var11);
    local_8._0_1_ = 3;
    ~basic_string<>();
    local_8._0_1_ = 2;
    ~basic_string<>();
    local_8._0_1_ = 1;
    ~basic_string<>();
    uVar2 = FID_conflict_begin(local_210);
    FUN_00747fe0(local_208,&local_1ec);
    cVar1 = FUN_004221b0(uVar2);
    if (cVar1 == '\0') {
      local_1bc = FUN_007470b0(&local_1ec,0);
      if ((*(char *)(local_1bc + 0xb7) == '\0') &&
         ((*(char *)(local_1bc + 0xb6) == '\0' || (*(char *)(local_1bc + 0xb0) == '\0')))) {
        cVar1 = FUN_0073ba10(local_1b0 + 10);
        if (cVar1 != '\0') {
          (**(code **)(*local_1b0 + 100))(local_1bc + 0x10);
          *(undefined1 *)(local_1bc + 0xb7) = 1;
          FUN_00578af0(local_220,local_1bc + 0x10);
        }
        FUN_00743f40(local_1bc,0);
        local_1b1 = '\x01';
      }
      FUN_00578b10(&local_1ec);
    }
    else {
      local_1b1 = '\x01';
      local_200 = FUN_0073cc40();
      local_8._0_1_ = 5;
      local_1f4 = local_200;
      FUN_00747db0(local_200);
      local_8._0_1_ = 1;
      FUN_0073cdf0();
      local_1c4 = FUN_0045e220();
      *(undefined4 *)(local_1c4 + 0x10) = local_1ec;
      *(undefined4 *)(local_1c4 + 0x14) = local_1e8;
      *(undefined4 *)(local_1c4 + 0x18) = local_1e4;
      *(undefined4 *)(local_1c4 + 0x1c) = local_1e0;
      FUN_00743f40(local_1c4,0);
      pcVar8 = FUN_004bc8c0;
      FUN_0081e820("Added lobby : ",local_1c4 + 0x68,&DAT_00896ce8,local_1c4 + 0x10);
      uVar2 = FUN_0081e660();
      uVar2 = FUN_004bc590(uVar2);
      uVar2 = FUN_00574730(uVar2);
      uVar2 = FUN_004bc590(uVar2);
      pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0073ba70(uVar2);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar8);
    }
  }
  if (*(char *)((int)local_1b0 + 0x62) == '\0') {
    FUN_00424640(local_1cc);
    FID_conflict_begin(local_1f8);
    while (cVar1 = FUN_00420f10(local_1f8), cVar1 != '\0') {
      FUN_0042d8c0(&local_1b8);
      FID_conflict_begin(local_1fc);
      local_204 = FUN_004237d0();
      while (cVar1 = FUN_00420f10(local_1fc), cVar1 != '\0') {
        uVar2 = local_204;
        FUN_0042da60(local_204);
        cVar1 = FUN_0056f780(uVar2);
        if (cVar1 != '\0') {
          iVar5 = FUN_0042da60();
          if (*(char *)(iVar5 + 0xb6) != '\0') {
            piVar12 = local_1b0 + 10;
            FUN_0042da60(piVar12);
            cVar1 = FUN_0073ba10(piVar12);
            if (cVar1 != '\0') {
              pcVar8 = FUN_004bc8c0;
              iVar5 = FUN_0042da60();
              iVar5 = FUN_0042da60(&DAT_00896ce8,iVar5 + 0x10);
              FUN_0081e820("Removing lobby : ",iVar5 + 0x68);
              uVar2 = FUN_0081e660();
              uVar2 = FUN_004bc590(uVar2);
              uVar2 = FUN_00574730(uVar2);
              uVar2 = FUN_004bc590(uVar2);
              pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0073ba70(uVar2);
              std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,pcVar8);
              local_1f0 = local_1b8;
              FUN_00747ca0(local_218,local_1b8);
              local_1b1 = '\x01';
            }
          }
          break;
        }
        FUN_0042da80();
      }
      FUN_00422190();
    }
  }
  puVar6 = (undefined4 *)FUN_0042d8c0(local_214);
  local_1c8 = *puVar6;
  puVar6 = (undefined4 *)FID_conflict_begin(local_20c);
  local_1d8[0] = *puVar6;
  if (local_1b1 != '\0') {
    FUN_007476a0();
  }
  local_1b0[0x15] = 2;
  if ((char)local_1b0[8] == '\0') {
    FUN_00429ce0();
  }
  local_1b0[0x15] = 2;
  cVar1 = FUN_004202c0();
  if (cVar1 != '\0') {
    (**(code **)(*local_1b0 + 8))();
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_0045c7d0();
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

