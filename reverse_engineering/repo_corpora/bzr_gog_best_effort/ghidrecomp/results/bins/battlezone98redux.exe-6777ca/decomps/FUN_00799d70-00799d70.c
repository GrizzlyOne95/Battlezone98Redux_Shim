
/* WARNING: Removing unreachable block (ram,0x0079a4a1) */
/* WARNING: Removing unreachable block (ram,0x0079b5c0) */

void FUN_00799d70(void)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar6;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar7;
  undefined4 *puVar8;
  undefined1 auStack_440 [140];
  undefined4 uStack_3b4;
  uint uStack_3b0;
  char *pcStack_3a8;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbStack_3a4;
  code *pcVar9;
  undefined1 auStack_378 [208];
  undefined1 *local_2a8;
  undefined1 *local_2a4;
  undefined4 local_2a0;
  undefined1 *local_298;
  undefined1 *local_294;
  undefined4 local_290;
  undefined4 local_28c;
  undefined1 *local_284;
  undefined4 local_280;
  undefined4 local_27c;
  undefined1 *local_274;
  undefined4 local_26c;
  undefined1 *local_268;
  undefined4 local_264;
  undefined4 local_260;
  undefined4 local_25c;
  undefined4 local_258;
  uint local_254;
  undefined4 local_250;
  uint local_24c;
  undefined4 local_248;
  undefined4 local_244;
  undefined4 local_240;
  undefined4 local_23c;
  undefined4 local_238;
  int local_234;
  int local_230;
  int local_22c;
  int local_228;
  char *local_224;
  int local_220;
  int *local_21c;
  undefined1 *local_218;
  undefined4 local_214;
  undefined1 local_20d;
  int local_20c;
  undefined4 local_208;
  undefined4 local_204;
  char *local_200;
  int local_1fc;
  int local_1f8;
  int local_1f4;
  uint local_1f0;
  int local_1ec;
  int local_1e8;
  int local_1e4;
  int local_1e0;
  int local_1dc;
  byte local_1d6;
  char local_1d5;
  int local_1d4;
  int local_1d0;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_16c [24];
  undefined4 local_154;
  undefined4 local_150;
  undefined4 local_14c;
  undefined4 local_148;
  undefined2 local_144;
  undefined4 local_128;
  undefined1 local_f4;
  undefined4 local_f0;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_d4 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_bc [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_a4 [24];
  XImage local_8c [48];
  undefined1 local_5c;
  undefined4 local_58;
  undefined1 local_3c;
  undefined1 local_3b;
  undefined1 local_3a;
  uint local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined1 local_2c;
  undefined4 local_28;
  undefined1 local_24;
  char local_20 [12];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085f759;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_1ec = FUN_006cc050();
  if (local_1ec == 0) {
    (**(code **)(**(int **)(local_1d0 + 0x174) + 0x3c))();
    if (*(int *)(local_1d0 + 0x170) != 0) {
      (**(code **)(**(int **)(local_1d0 + 0x170) + 0x3c))();
    }
    FUN_0081cb40();
    (**(code **)(**(int **)(local_1d0 + 0x180) + 0x3c))();
    (**(code **)(**(int **)(local_1d0 + 0x158) + 0x24))();
  }
  else if (local_1ec == 1) {
    (**(code **)(**(int **)(local_1d0 + 0x174) + 0x3c))();
    if (*(int *)(local_1d0 + 0x170) != 0) {
      (**(code **)(**(int **)(local_1d0 + 0x170) + 0x3c))();
    }
    FUN_0081cb40();
    (**(code **)(**(int **)(local_1d0 + 0x180) + 0x3c))();
    (**(code **)(**(int **)(local_1d0 + 0x158) + 0x24))();
  }
  else if (local_1ec == 2) {
    (**(code **)(**(int **)(local_1d0 + 0x174) + 0x3c))();
    if (*(int *)(local_1d0 + 0x170) != 0) {
      (**(code **)(**(int **)(local_1d0 + 0x170) + 0x3c))();
    }
    FUN_0081cb40();
    (**(code **)(**(int **)(local_1d0 + 0x180) + 0x3c))();
    (**(code **)(**(int **)(local_1d0 + 0x158) + 0x24))();
    cVar1 = FUN_007c7a40();
    if (cVar1 != '\0') {
      local_23c = *(undefined4 *)(local_1d0 + 0x138);
      FUN_0081e820();
      FUN_0081e710();
      FUN_007c7960();
      FUN_007c79d0();
    }
  }
  else if (local_1ec == 3) {
    (**(code **)(**(int **)(local_1d0 + 0x174) + 0x3c))();
    if (*(int *)(local_1d0 + 0x170) != 0) {
      (**(code **)(**(int **)(local_1d0 + 0x170) + 0x3c))();
    }
    FUN_0081cb40();
    (**(code **)(**(int **)(local_1d0 + 0x180) + 0x3c))();
    (**(code **)(**(int **)(local_1d0 + 0x158) + 0x24))();
  }
  else if (local_1ec == 4) {
    local_1dc = FUN_0056f900();
    if (local_1dc == 0) {
      if (*(int *)(local_1d0 + 0x170) != 0) {
        (**(code **)(**(int **)(local_1d0 + 0x170) + 0x3c))();
      }
      goto LAB_0079b6ab;
    }
    if (*(int *)(local_1d0 + 0x170) != 0) {
      local_25c = FUN_0073a9f0();
      local_8 = 0;
      local_258 = local_25c;
      FUN_0041f870();
      (**(code **)(**(int **)(local_1d0 + 0x170) + 0x3c))();
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    if (*(char *)(local_1dc + 0xb0) != '\0') {
      local_214 = *(undefined4 *)(local_1d0 + 0x138);
      FUN_0081e820();
      FUN_0081e710();
      FUN_007c7960();
      FUN_007c79d0();
      goto LAB_0079b6ab;
    }
    FUN_007c3040();
    FUN_007a8c60();
    local_244 = FUN_0081cb40();
    local_250 = FUN_0081cb40();
    local_238 = local_250;
    if (*(char *)(local_1dc + 0x148) == '\0') {
      local_238 = local_244;
    }
    (**(code **)(**(int **)(local_1d0 + 0x178) + 0x3c))();
    local_1fc = 0;
    while (iVar3 = size(), local_1fc < iVar3) {
      FUN_00742cf0();
      FUN_004200d0();
      FUN_007c4690();
      local_1fc = local_1fc + 1;
    }
    local_1d4 = FUN_0056f900();
    (**(code **)(**(int **)(local_1d0 + 0x1bc) + 0x38))();
    local_1e0 = FUN_00746690();
    CMFCRibbonInfo::XImage::XImage(local_8c);
    local_8 = 1;
    if (local_1d4 != 0) {
      FID_conflict_operator_();
      local_3a = *(undefined1 *)(local_1d4 + 0x116);
      local_3b = *(undefined1 *)(local_1d4 + 0x115);
      FID_conflict_operator_();
      local_5c = *(undefined1 *)(local_1d4 + 0xf4);
      FID_conflict_operator_();
      local_58 = *(undefined4 *)(local_1d4 + 0xf8);
      local_28 = *(undefined4 *)(local_1d4 + 0x128);
      local_30 = *(undefined4 *)(local_1d4 + 0x120);
      local_34 = *(undefined4 *)(local_1d4 + 0x11c);
      local_2c = *(undefined1 *)(local_1d4 + 0x124);
      local_24 = *(undefined1 *)(local_1d4 + 300);
      local_3c = *(undefined1 *)(local_1d4 + 0x114);
      local_38 = *(uint *)(local_1d4 + 0x118);
      if (0x168 < local_38) {
        local_38 = 0;
      }
      iVar3 = FUN_0056f900();
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (local_16c,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 (iVar3 + 0xdc));
      local_8._0_1_ = 2;
      FUN_007a3e60();
      FUN_007aa560();
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (local_bc,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)local_8c);
      local_8 = CONCAT31(local_8._1_3_,3);
      local_2a0 = 0x23;
      uVar4 = FUN_004170c0();
      if (0x23 < uVar4) {
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::resize
                  (local_bc,0x23);
      }
      FUN_0041f870();
      (**(code **)(**(int **)(local_1d0 + 0x174) + 0x3c))();
      FUN_0056f900();
      FUN_007c4530();
      FUN_0056f900();
      FUN_007c4530();
      FUN_0056f900();
      FUN_007c4530();
      FUN_007c4530();
      FUN_0056f900();
      FUN_007c4530();
      FUN_0081cb40();
      basic_string<>();
      local_8 = CONCAT31(local_8._1_3_,4);
      iVar3 = FUN_0056f900();
      if (*(int *)(iVar3 + 0x118) == 0) {
        local_2a8 = (undefined1 *)&pcStack_3a8;
        uStack_3b0 = 0x79a695;
        local_28c = std::
                    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                *)&pcStack_3a8,local_d4);
        FUN_007c44a0();
      }
      else {
        iVar3 = FUN_0056f900();
        local_24c = *(uint *)(iVar3 + 0x118) % 0x3c;
        iVar3 = FUN_0056f900();
        local_254 = *(uint *)(iVar3 + 0x118) / 0x3c;
        pbStack_3a4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)0x79a71a;
        sprintf(local_20,"%d:%02d");
        local_268 = (undefined1 *)&pcStack_3a8;
        uStack_3b0 = 0x79a731;
        local_280 = basic_string<>();
        FUN_007c44a0();
      }
      if (*(int *)(local_1d4 + 0x128) == 0) {
        local_274 = (undefined1 *)&pcStack_3a8;
        uStack_3b0 = 0x79a7ba;
        local_27c = std::
                    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                *)&pcStack_3a8,local_d4);
        FUN_007c44a0();
      }
      else {
        sprintf(local_20,"%2u");
        local_2a4 = (undefined1 *)&pcStack_3a8;
        uStack_3b0 = 0x79a78a;
        local_26c = basic_string<>();
        FUN_007c44a0();
      }
      sprintf(local_20,"%u");
      local_284 = (undefined1 *)&pcStack_3a8;
      uStack_3b0 = 0x79a804;
      local_290 = basic_string<>();
      FUN_007c44a0();
      sprintf(local_20,"%u");
      local_298 = (undefined1 *)&pcStack_3a8;
      uStack_3b0 = 0x79a84e;
      local_264 = basic_string<>();
      FUN_007c44a0();
      local_20c = FUN_007a4220();
      if (local_20c == 0) {
        (**(code **)(**(int **)(local_1d0 + 0x198) + 0x24))();
        (**(code **)(**(int **)(local_1d0 + 0x1ac) + 0x24))();
        (**(code **)(**(int **)(local_1d0 + 0x194) + 0x24))();
        pbStack_3a4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)0x79aaf6;
        (**(code **)(**(int **)(local_1d0 + 0x1a8) + 0x24))();
        pbStack_3a4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)0x0;
        pcStack_3a8 = "j";
        (**(code **)(**(int **)(local_1d0 + 0x18c) + 0x24))();
        pcStack_3a8 = (char *)0x0;
        (**(code **)(**(int **)(local_1d0 + 400) + 0x24))();
      }
      else {
        local_1d5 = *(char *)(local_20c + 0x38);
        if (((local_1d5 == 'D') || (local_1d5 == 'A')) || (local_1d5 == 'K')) {
          (**(code **)(**(int **)(local_1d0 + 0x198) + 0x24))();
          (**(code **)(**(int **)(local_1d0 + 0x1ac) + 0x24))();
          (**(code **)(**(int **)(local_1d0 + 0x194) + 0x24))();
          pbStack_3a4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)0x79a944;
          (**(code **)(**(int **)(local_1d0 + 0x1a8) + 0x24))();
          pbStack_3a4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)0x0;
          pcStack_3a8 = "j";
          (**(code **)(**(int **)(local_1d0 + 0x18c) + 0x24))();
          pcStack_3a8 = (char *)0x0;
          (**(code **)(**(int **)(local_1d0 + 400) + 0x24))();
        }
        else if ((local_1d5 == 'S') || (local_1d5 == 'M')) {
          (**(code **)(**(int **)(local_1d0 + 0x198) + 0x24))();
          (**(code **)(**(int **)(local_1d0 + 0x1ac) + 0x24))();
          (**(code **)(**(int **)(local_1d0 + 0x194) + 0x24))();
          pbStack_3a4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)0x79aa2b;
          (**(code **)(**(int **)(local_1d0 + 0x1a8) + 0x24))();
          pbStack_3a4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)0x1;
          pcStack_3a8 = (char *)0x79aa4c;
          (**(code **)(**(int **)(local_1d0 + 0x18c) + 0x24))();
          pcStack_3a8 = (char *)0x1;
          (**(code **)(**(int **)(local_1d0 + 400) + 0x24))();
        }
      }
      if ((*(char *)(local_1d0 + 0x1d5) == '\0') ||
         (cVar1 = FUN_00742cf0(), cVar1 != *(char *)(local_1d0 + 0x1d4))) {
        *(undefined1 *)(local_1d0 + 0x1d5) = 1;
        uVar2 = FUN_00742cf0();
        *(undefined1 *)(local_1d0 + 0x1d4) = uVar2;
        FUN_00742cf0();
        FUN_007c3040();
        FUN_00742cf0();
        FUN_007a3d20();
      }
      cVar1 = FUN_00742cf0();
      if (cVar1 != '\0') {
        local_220 = *(int *)(local_1d4 + 0x120);
        FUN_0056f900();
        local_228 = (**(code **)(**(int **)(local_1d0 + 0x1bc) + 0x3c))();
        if (local_220 != local_228) {
          local_1e8 = local_220;
          FUN_0056f900();
          local_230 = (**(code **)(**(int **)(local_1d0 + 0x1bc) + 0x44))();
          if (local_1e8 < local_230) {
            local_1e8 = local_230;
          }
          if (local_1e8 != local_228) {
            FUN_00574400();
            local_8._0_1_ = 5;
            if (&stack0x00000000 == (undefined1 *)0x388) {
              local_218 = (undefined1 *)0x0;
            }
            else {
              local_218 = auStack_378;
            }
            pcVar9 = FUN_004bc8c0;
            pbStack_3a4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)0x79ad2f;
            iVar3 = local_1e8;
            iVar5 = FUN_0056f900();
            pbStack_3a4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)(iVar5 + 0x10);
            pcStack_3a8 = "CNetGameLobby::OnDataChanged, adjusting lobby ";
            uStack_3b0 = 0x79ad44;
            pcStack_3a8 = (char *)FUN_004bc590();
            pbStack_3a4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)FUN_0073ba70();
            pcStack_3a8 = (char *)0x79ad56;
            pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
            std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,iVar3);
            pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
            std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,pcVar9);
            pbVar7 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
            FUN_0081e820();
            pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
            std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,pbVar7);
            FUN_0056f900();
            (**(code **)(**(int **)(local_1d0 + 0x1bc) + 0x40))();
            local_8 = CONCAT31(local_8._1_3_,4);
            FUN_00417f10();
          }
        }
      }
      if ((local_1d4 == 0) || (local_1e0 == 0)) {
        local_200 = "Loading";
        if (*(char **)(local_1d0 + 0x144) != "Loading") {
          (**(code **)(**(int **)(local_1d0 + 0x180) + 0x3c))();
          *(char **)(local_1d0 + 0x144) = local_200;
        }
        (**(code **)(**(int **)(local_1d0 + 0x158) + 0x24))();
      }
      else {
        FUN_0079b780();
        local_8._0_1_ = 6;
        local_154 = *(undefined4 *)(local_1e0 + 8);
        local_150 = *(undefined4 *)(local_1e0 + 0xc);
        local_14c = *(undefined4 *)(local_1e0 + 0x10);
        local_148 = *(undefined4 *)(local_1e0 + 0x14);
        local_144 = *(undefined2 *)(local_1e0 + 0x28);
        local_128 = *(undefined4 *)(local_1e0 + 0x80);
        FID_conflict_operator_();
        FID_conflict_operator_();
        FID_conflict_operator_();
        local_f0 = *(undefined4 *)(local_1dc + 0x4c);
        local_f4 = *(undefined1 *)(local_1dc + 0x48);
        FID_conflict_operator_();
        FUN_0056f8b0();
        local_1d6 = FUN_0056f780();
        local_20d = 0;
        local_1f0 = 0;
        local_1f4 = 0;
        puVar8 = (undefined4 *)FUN_0042d8c0();
        local_204 = *puVar8;
        puVar8 = (undefined4 *)FID_conflict_begin();
        local_240 = *puVar8;
        cVar1 = FUN_00420f10();
        if (cVar1 != '\0') {
          FUN_004305e0();
          cVar1 = FUN_0073ba10();
          if (cVar1 != '\0') {
            local_1f0 = local_1f0 + 1;
            iVar3 = FUN_004305e0();
            if (*(char *)(iVar3 + 0x60) != '\0') {
              local_1f4 = local_1f4 + 1;
            }
          }
                    /* WARNING: Subroutine does not return */
          FUN_0042de70();
        }
        local_1e4 = 0;
        pbStack_3a4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)local_1f0;
        pcStack_3a8 = (char *)(uint)*(byte *)(local_1e0 + 0x60);
        uStack_3b0 = (uint)local_1d6;
        uStack_3b4 = 0x79b026;
        local_1f8 = FUN_00573d00();
        if ((local_1f8 == 4) && (cVar1 = FUN_00742cf0(), cVar1 != '\0')) {
          puVar8 = (undefined4 *)FUN_0042d8c0();
          local_208 = *puVar8;
          puVar8 = (undefined4 *)FID_conflict_begin();
          local_248 = *puVar8;
          cVar1 = FUN_00420f10();
          if (cVar1 != '\0') {
            local_22c = FUN_00422e80();
            basic_string<>();
            local_8._0_1_ = 7;
            basic_string<>();
            local_8._0_1_ = 8;
            local_21c = (int *)FUN_00764760();
            local_224 = (char *)(**(code **)(*local_21c + 0x28))();
            local_8 = CONCAT31(local_8._1_3_,7);
            ~basic_string<>();
            if (local_224 != (char *)0x0) {
              pbStack_3a4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             *)0x79b152;
              std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
              operator=(local_a4,local_224);
            }
            pbStack_3a4 = local_a4;
            pcStack_3a8 = (char *)0x79b168;
            cVar1 = operator!=<>();
            if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
              FUN_0042de70();
            }
            pbStack_3a4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)(local_22c + 0x2c);
            pcStack_3a8 = "User ";
            FUN_0081e820();
            FUN_0081e660();
            uStack_3b0 = 0x79b198;
            pcStack_3a8 = (char *)FUN_004bc590();
            pbStack_3a4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)FUN_00574730();
            pcStack_3a8 = (char *)0x79b1aa;
            FUN_004bc590();
            local_1f8 = 1;
            local_1e4 = FUN_0081cb40();
            local_8._0_1_ = 6;
            ~basic_string<>();
          }
        }
        if (local_1e4 != *(int *)(local_1d0 + 0x144)) {
          if (local_1e4 == 0) {
            (**(code **)(**(int **)(local_1d0 + 0x180) + 0x3c))();
          }
          else {
            (**(code **)(**(int **)(local_1d0 + 0x180) + 0x3c))();
          }
          *(int *)(local_1d0 + 0x144) = local_1e4;
        }
        local_234 = local_1f8;
        switch(local_1f8) {
        case 0:
          (**(code **)(**(int **)(local_1d0 + 0x158) + 0x24))();
          break;
        case 1:
        case 4:
          (**(code **)(**(int **)(local_1d0 + 0x158) + 0x24))();
          FUN_0081cb40();
          FUN_007c2950();
          break;
        case 2:
          (**(code **)(**(int **)(local_1d0 + 0x158) + 0x24))();
          FUN_0081cb40();
          FUN_007c2950();
          break;
        case 3:
          (**(code **)(**(int **)(local_1d0 + 0x158) + 0x24))();
          FUN_0081cb40();
          FUN_007c2950();
          break;
        default:
          (**(code **)(**(int **)(local_1d0 + 0x158) + 0x24))();
        }
        if ((local_1f8 == 4) && (*(char *)(local_1e0 + 0x7c) == '\0')) {
          pbStack_3a4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         *)(uint)*(byte *)(local_1d4 + 0xb1);
          pcStack_3a8 = (char *)(uint)local_1d6;
          cVar1 = FUN_005740a0();
          if (cVar1 != '\0') {
            if (local_1d6 != 0) {
              FUN_00742df0();
            }
            *(undefined1 *)(local_1e0 + 0x7c) = 1;
            basic_string<>();
            local_8._0_1_ = 9;
            basic_string<>();
            local_8._0_1_ = 10;
            FUN_0073bcf0();
            (**(code **)(**(int **)(local_1d0 + 0x1bc) + 0x1c))();
            local_8._0_1_ = 9;
            ~basic_string<>();
            local_8._0_1_ = 6;
            ~basic_string<>();
            FUN_00434170();
            DAT_00918328 = 0;
            FUN_007c9170();
            FUN_0078bb00();
            FUN_007c7930();
            local_294 = auStack_440;
            local_260 = FUN_00753550(local_20c);
            FUN_0076e660();
            FUN_0081e820();
            FUN_0081e710();
          }
        }
        local_8 = CONCAT31(local_8._1_3_,4);
        CCommandManager::ClearAllCmdImages((CCommandManager *)&local_154);
      }
      local_8._0_1_ = 3;
      ~basic_string<>();
      local_8._0_1_ = 2;
      ~basic_string<>();
      local_8 = CONCAT31(local_8._1_3_,1);
      ~basic_string<>();
    }
    local_8 = 0xffffffff;
    FUN_0079b750();
  }
  else if (*(int *)(local_1d0 + 0x170) != 0) {
    (**(code **)(**(int **)(local_1d0 + 0x170) + 0x3c))();
  }
  if (*(int *)(local_1d0 + 0x1bc) != 0) {
    FUN_007ce580();
  }
LAB_0079b6ab:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

