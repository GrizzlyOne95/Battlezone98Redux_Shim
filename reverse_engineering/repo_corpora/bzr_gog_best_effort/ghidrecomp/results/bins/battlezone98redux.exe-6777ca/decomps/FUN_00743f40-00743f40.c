
void FUN_00743f40(int param_1)

{
  undefined1 uVar1;
  char cVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar7;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar8;
  undefined8 uVar9;
  code *pcVar10;
  undefined *puVar11;
  undefined1 auStack_260 [160];
  undefined1 local_1c0 [16];
  undefined1 local_1b0 [16];
  undefined1 local_1a0 [8];
  undefined1 local_198 [4];
  undefined1 local_194 [4];
  undefined1 local_190 [4];
  undefined4 local_18c;
  undefined4 local_188;
  undefined4 local_184;
  undefined4 local_180;
  undefined1 local_17c [12];
  undefined1 *local_170;
  undefined4 local_16c;
  undefined1 local_168 [4];
  char *local_164;
  char *local_160;
  undefined4 local_15c;
  char *local_158;
  char *local_154;
  undefined4 local_150;
  char local_14a;
  undefined1 local_149;
  int *local_148;
  undefined1 local_144 [4];
  undefined1 local_140 [84];
  undefined1 local_ec [24];
  undefined1 local_d4 [24];
  undefined1 local_bc [24];
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b448;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar3;
  basic_string<>("gameType");
  local_8 = 0;
  local_158 = (char *)(**(code **)(*local_148 + 0x2c))(param_1 + 0x10,local_8c,uVar3);
  local_8 = 0xffffffff;
  ~basic_string<>();
  if ((local_158 == (char *)0x0) || (*local_158 == '\0')) {
    *(undefined1 *)(param_1 + 0x148) = 1;
  }
  else if (*local_158 == '1') {
    *(undefined1 *)(param_1 + 0x148) = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x148) = 1;
  }
  basic_string<>(&DAT_00879d2c);
  local_8 = 1;
  local_154 = (char *)(**(code **)(*local_148 + 0x2c))(param_1 + 0x10,local_bc);
  local_8 = 0xffffffff;
  ~basic_string<>();
  basic_string<>(local_154);
  local_8 = 2;
  FUN_0073d480(local_17c,local_2c,*PTR_DAT_008eda34);
  local_8 = CONCAT31(local_8._1_3_,3);
  (**(code **)(*local_148 + 0x68))(&local_18c,param_1 + 0x10);
  uVar1 = (**(code **)(*local_148 + 0x30))(param_1 + 0x10);
  *(undefined1 *)(param_1 + 0xb3) = uVar1;
  cVar2 = FUN_0073ba10(param_1 + 0x20);
  if (cVar2 != '\0') {
    uVar4 = (**(code **)(*local_148 + 0x38))(local_1c0);
    cVar2 = FUN_0056f780(uVar4);
    if (cVar2 != '\0') {
      FUN_0042d8c0(&local_150);
      FID_conflict_begin(local_168);
      while (cVar2 = FUN_00420f10(local_168), cVar2 != '\0') {
        uVar4 = FUN_0042de50();
        FUN_007467b0(uVar4);
        FUN_0042da80();
      }
      if (DAT_00917f48 == 0) {
        if (*(char *)(param_1 + 0xb1) != '\0') {
          local_14a = '\0';
          puVar5 = (undefined4 *)FUN_0042d8c0(local_194);
          local_150 = *puVar5;
          while (cVar2 = FUN_00420f10(local_168), cVar2 != '\0') {
            iVar6 = FUN_0042da60();
            if (*(char *)(iVar6 + 0x7c) != '\0') {
              iVar6 = param_1 + 0x20;
              FUN_0042da60(iVar6);
              cVar2 = FUN_0073ba10(iVar6);
              if (cVar2 != '\0') {
                iVar6 = FUN_0042da60();
                cVar2 = (**(code **)(*local_148 + 0x6c))(param_1 + 0x10,iVar6 + 8);
                if (cVar2 != '\0') {
                  local_14a = '\0';
                  break;
                }
              }
            }
            FUN_0042da80();
          }
          if (local_14a == '\0') {
            basic_string<>("launched");
            local_8._0_1_ = 4;
            (**(code **)(*local_148 + 0x24))(param_1 + 0x10,local_ec);
            local_8 = CONCAT31(local_8._1_3_,3);
            ~basic_string<>();
            *(undefined1 *)(param_1 + 0xb1) = 0;
          }
        }
      }
      else {
        FUN_00578760();
      }
    }
    *(undefined4 *)(param_1 + 0x20) = local_18c;
    *(undefined4 *)(param_1 + 0x24) = local_188;
    *(undefined4 *)(param_1 + 0x28) = local_184;
    *(undefined4 *)(param_1 + 0x2c) = local_180;
  }
  *(undefined1 *)(param_1 + 0xb7) = 0;
  if ((local_154 == (char *)0x0) || (*local_154 == '\0')) {
    if (*(char *)(param_1 + 0xb7) == '\0') {
      *(undefined1 *)(param_1 + 0xb7) = 1;
      *(undefined1 *)(param_1 + 0xb0) = 1;
      FUN_00578af0(local_1a0,param_1 + 0x10);
      FUN_00574400(3,1);
      local_8._0_1_ = 6;
      if (&stack0x00000000 == (undefined1 *)0x270) {
        local_170 = (undefined1 *)0x0;
      }
      else {
        local_170 = auStack_260;
      }
      pcVar10 = FUN_004bc8c0;
      uVar4 = FUN_004bc590(local_170,
                           "CNetGameLobby::PopulateLobbyFromData, requesting missing data for lobby "
                           ,param_1 + 0x10);
      pbVar8 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0073ba70(uVar4);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar8,pcVar10);
      pbVar7 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
      FUN_0081e820();
      pbVar8 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar8,pbVar7);
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 (param_1 + 0x68),"***");
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 (param_1 + 0x80),"Loading Room...");
      (**(code **)(*local_148 + 100))(param_1 + 0x10);
      local_8 = CONCAT31(local_8._1_3_,3);
      FUN_00417f10();
    }
  }
  else {
    uVar4 = FID_conflict_begin(local_190);
    FUN_00747fe0(local_198,param_1 + 0x10);
    cVar2 = FUN_00420f10(uVar4);
    if (cVar2 != '\0') {
      uVar9 = FUN_00822ea0();
      *(undefined8 *)(local_148 + 0x20) = uVar9;
    }
    FUN_00578b10(param_1 + 0x10);
    uVar3 = FUN_0048a830();
    if (uVar3 < 5) {
      *(undefined1 *)(param_1 + 0xb4) = 1;
      *(undefined1 *)(param_1 + 0xb0) = 1;
      FID_conflict_operator_(local_2c);
      basic_string<>("-non-BZ-");
      local_8._0_1_ = 5;
      FUN_00449810(local_2c);
      FID_conflict_operator_(local_2c);
      FID_conflict_operator_(local_44);
      local_8 = CONCAT31(local_8._1_3_,3);
      ~basic_string<>();
    }
    else {
      *(undefined1 *)(param_1 + 0xb4) = 1;
      *(undefined1 *)(param_1 + 0xb6) = 1;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 (param_1 + 0x68),local_154);
      uVar4 = FUN_006cf480(4);
      FID_conflict_operator_(uVar4);
      puVar11 = &DAT_0087bb64;
      uVar4 = FUN_006cf480(1);
      uVar1 = operator!=<>(uVar4,puVar11);
      *(undefined1 *)(param_1 + 0xb0) = uVar1;
      puVar11 = &DAT_0089a7c4;
      uVar4 = FUN_006cf480(2);
      uVar1 = FUN_00427270(uVar4,puVar11);
      *(undefined1 *)(param_1 + 0xb2) = uVar1;
      uVar4 = FUN_006cf480(3);
      FID_conflict_operator_(uVar4);
    }
  }
  cVar2 = FUN_0056f780(local_148 + 10);
  if (cVar2 != '\0') {
    *(undefined1 *)((int)local_148 + 0x21) = *(undefined1 *)(param_1 + 0xb0);
  }
  if ((*(char *)(param_1 + 0xb4) != '\0') && (*(char *)(param_1 + 0xb0) == '\0')) {
    basic_string<>("gameSettings");
    local_8._0_1_ = 7;
    uVar4 = (**(code **)(*local_148 + 0x2c))(param_1 + 0x10,local_a4);
    basic_string<>(uVar4);
    local_8._0_1_ = 9;
    ~basic_string<>();
    FUN_0073bbd0();
    local_8 = CONCAT31(local_8._1_3_,10);
    cVar2 = FUN_0073c450(local_5c);
    if (cVar2 != '\0') {
      local_149 = 0;
      cVar2 = FUN_0056f780(local_148 + 10);
      if ((cVar2 != '\0') && (cVar2 = operator!=<>(local_140,param_1 + 0xdc), cVar2 != '\0')) {
        local_149 = 1;
      }
      uVar4 = (**(code **)(*local_148 + 0x38))(local_1b0);
      cVar2 = FUN_0073ba10(uVar4);
      if (cVar2 != '\0') {
        FID_conflict_operator_(local_5c);
        FUN_0073cb70(local_144);
      }
      FUN_00742ee0(param_1,local_149);
      if (*(char *)(param_1 + 0xb1) == '\0') {
        basic_string<>("launched");
        local_8._0_1_ = 0xb;
        local_160 = (char *)(**(code **)(*local_148 + 0x2c))(param_1 + 0x10,local_74);
        local_8 = CONCAT31(local_8._1_3_,10);
        ~basic_string<>();
        if ((local_160 == (char *)0x0) || (*local_160 != '1')) {
          local_16c = 0;
        }
        else {
          local_16c = 1;
        }
        *(undefined1 *)(param_1 + 0xb1) = (undefined1)local_16c;
        if (*(char *)(param_1 + 0xb1) != '\0') {
          pcVar10 = FUN_0056f740;
          FUN_0081e820("Lobby ",param_1 + 0x10,FUN_0056f740,&DAT_00884900,param_1 + 0x80,
                       ") GAME Launched\n");
          uVar4 = FUN_0081e660();
          uVar4 = FUN_004bc590(uVar4);
          pbVar8 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0073ba70(uVar4);
          pbVar8 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                             (pbVar8,pcVar10);
          uVar4 = FUN_004bc590(pbVar8);
          uVar4 = FUN_00574730(uVar4);
          FUN_004bc590(uVar4);
        }
      }
      else {
        basic_string<>("launched");
        local_8._0_1_ = 0xc;
        local_164 = (char *)(**(code **)(*local_148 + 0x2c))(param_1 + 0x10,local_d4);
        local_8 = CONCAT31(local_8._1_3_,10);
        ~basic_string<>();
        if ((local_164 == (char *)0x0) || (*local_164 != '1')) {
          local_15c = 0;
        }
        else {
          local_15c = 1;
        }
        *(undefined1 *)(param_1 + 0xb1) = (undefined1)local_15c;
        if (*(char *)(param_1 + 0xb1) == '\0') {
          pcVar10 = FUN_0056f740;
          FUN_0081e820("Lobby ",param_1 + 0x10,FUN_0056f740,&DAT_00884900,param_1 + 0x80,
                       ") GAME Launch Revoked (no players remaining in game)\n");
          uVar4 = FUN_0081e660();
          uVar4 = FUN_004bc590(uVar4);
          pbVar8 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0073ba70(uVar4);
          pbVar8 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                             (pbVar8,pcVar10);
          uVar4 = FUN_004bc590(pbVar8);
          uVar4 = FUN_00574730(uVar4);
          FUN_004bc590(uVar4);
        }
      }
    }
    local_8._0_1_ = 9;
    FUN_0073cb40();
    local_8 = CONCAT31(local_8._1_3_,3);
    ~basic_string<>();
  }
  if ((((*(char *)((int)local_148 + 0x62) != '\0') && (*(char *)(param_1 + 0xb5) != '\0')) &&
      (cVar2 = FUN_0056f780(local_148 + 10), cVar2 != '\0')) && (*(char *)(param_1 + 0xb4) != '\0'))
  {
    *(undefined1 *)(param_1 + 0xb5) = 0;
    *(undefined1 *)((int)local_148 + 0x62) = 0;
    FUN_007464e0(4);
    FUN_00795c90();
  }
  if ((local_148[0x15] == 2) && (cVar2 = FUN_004202c0(), cVar2 != '\0')) {
    (**(code **)(*local_148 + 8))();
  }
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_0048a040();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

