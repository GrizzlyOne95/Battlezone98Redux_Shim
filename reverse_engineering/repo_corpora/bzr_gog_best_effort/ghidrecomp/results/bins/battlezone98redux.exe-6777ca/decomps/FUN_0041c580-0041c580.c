
void FUN_0041c580(void)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar3;
  char *pcVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined1 *puVar7;
  undefined1 local_348 [220];
  int local_26c [44];
  undefined1 local_1bc [4];
  undefined1 local_1b8 [4];
  uint local_1b4;
  undefined4 local_1b0;
  undefined4 local_1ac;
  uint local_1a8;
  uint local_1a4;
  byte *local_1a0;
  int *local_19c;
  char *local_198;
  byte *local_194;
  byte *local_190;
  int local_18c;
  byte local_186;
  byte local_185;
  int local_184;
  undefined1 local_180 [48];
  undefined1 local_150 [24];
  undefined4 local_138;
  undefined1 local_134 [4];
  undefined1 local_130 [4];
  undefined1 local_12c [4];
  undefined1 local_128 [4];
  undefined1 local_124 [24];
  undefined4 local_10c;
  undefined1 local_108 [24];
  undefined4 local_f0;
  undefined1 local_e8 [24];
  undefined4 local_d0;
  undefined4 local_cc;
  undefined1 local_bc [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_a4 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844ef3;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_0041fde0(local_14);
  FUN_004202f0();
  basic_string<>();
  local_8 = 0;
  basic_string<>(&DAT_02cf0000);
  local_8._0_1_ = 1;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_8c,"\\");
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_8c,"giddi");
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_8c,"\\");
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_8c,"inputmbl.txt");
  FUN_00426a60(&DAT_02cf2000,0);
  local_8._0_1_ = 2;
  FUN_00426af0("config.ini");
  FUN_00421fc0(1);
  local_8 = CONCAT31(local_8._1_3_,3);
  uVar6 = 0x40;
  uVar5 = 1;
  uVar3 = FUN_0041f870(1,0x40);
  FUN_004220f0(uVar3,uVar5,uVar6);
LAB_0041c68b:
  local_19c = (int *)FUN_004272d0(local_348,local_a4);
  bVar1 = std::ios_base::operator_bool((ios_base *)((int)local_19c + *(int *)(*local_19c + 4)));
  if (bVar1) {
    cVar2 = FUN_0041f890();
    if ((cVar2 == '\0') &&
       (pcVar4 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                 operator[](local_a4,0), *pcVar4 != '#')) {
      FUN_00417cc0();
      local_8._0_1_ = 4;
      FUN_004203f0(local_a4,3,1);
      local_8._0_1_ = 5;
      basic_string<>();
      local_8._0_1_ = 6;
      FUN_004272a0(local_26c,local_44,0x3b);
      cVar2 = FUN_00427270(local_44,"default");
      if (cVar2 != '\0') {
        FUN_004272a0(local_26c,local_184 + 0x44,0x3b);
        local_8._0_1_ = 5;
        ~basic_string<>();
        local_8._0_1_ = 4;
        FUN_00417f10();
        local_8 = CONCAT31(local_8._1_3_,3);
        FUN_0041d0b0();
        goto LAB_0041c68b;
      }
      FUN_004272a0(local_26c,local_150,0x3b);
      basic_string<>();
      local_8._0_1_ = 7;
      FUN_004272a0(local_26c,local_2c,0x3b);
      cVar2 = FUN_00427270(local_2c,"ANALOG");
      if (cVar2 == '\0') {
        cVar2 = FUN_00427270(local_2c,&DAT_00871354);
        if (cVar2 == '\0') {
          cVar2 = FUN_00427270(local_2c,"STANDARD");
          if (cVar2 == '\0') {
            cVar2 = FUN_00427270(local_2c,&DAT_008712e4);
            if (cVar2 == '\0') {
              cVar2 = FUN_00427270(local_2c,"MASTER");
              if (cVar2 == '\0') {
                cVar2 = FUN_00427270(local_2c,"ALTERNATE");
                if (cVar2 == '\0') {
                  cVar2 = FUN_00427270(local_2c,"DWEAPON");
                  if (cVar2 == '\0') {
                    cVar2 = FUN_00427270(local_2c,"INVISIBLE");
                    if (cVar2 == '\0') {
                      cVar2 = FUN_00427270(local_2c,&DAT_00871390);
                      if (cVar2 == '\0') {
                        local_8._0_1_ = 6;
                        ~basic_string<>();
                        local_8._0_1_ = 5;
                        ~basic_string<>();
                        local_8._0_1_ = 4;
                        FUN_00417f10();
                        local_8 = CONCAT31(local_8._1_3_,3);
                        FUN_0041d0b0();
                        goto LAB_0041c68b;
                      }
                      local_138 = 2;
                    }
                    else {
                      local_138 = 8;
                    }
                  }
                  else {
                    local_138 = 7;
                  }
                }
                else {
                  local_138 = 6;
                }
              }
              else {
                local_138 = 5;
              }
            }
            else {
              local_138 = 4;
            }
          }
          else {
            local_138 = 3;
          }
        }
        else {
          local_138 = 9;
        }
      }
      else {
        local_138 = 10;
      }
      local_18c = 0;
      basic_string<>();
      local_8._0_1_ = 8;
      FUN_004272a0(local_26c,local_5c,0x3b);
      cVar2 = FUN_0041f890();
      if ((cVar2 == '\0') && (local_18c = FUN_0041d170(local_44,local_5c), local_18c == 0)) {
        local_8._0_1_ = 7;
        ~basic_string<>();
        local_8._0_1_ = 6;
        ~basic_string<>();
        local_8._0_1_ = 5;
        ~basic_string<>();
        local_8._0_1_ = 4;
        FUN_00417f10();
        local_8 = CONCAT31(local_8._1_3_,3);
        FUN_0041d0b0();
      }
      else {
        cVar2 = FUN_0041c520(local_26c,local_134);
        if (cVar2 == '\0') {
          local_8._0_1_ = 7;
          ~basic_string<>();
          local_8._0_1_ = 6;
          ~basic_string<>();
          local_8._0_1_ = 5;
          ~basic_string<>();
          local_8._0_1_ = 4;
          FUN_00417f10();
          local_8 = CONCAT31(local_8._1_3_,3);
          FUN_0041d0b0();
        }
        else {
          cVar2 = FUN_0041c520(local_26c,local_130);
          if (cVar2 == '\0') {
            local_8._0_1_ = 7;
            ~basic_string<>();
            local_8._0_1_ = 6;
            ~basic_string<>();
            local_8._0_1_ = 5;
            ~basic_string<>();
            local_8._0_1_ = 4;
            FUN_00417f10();
            local_8 = CONCAT31(local_8._1_3_,3);
            FUN_0041d0b0();
          }
          else {
            cVar2 = FUN_0041c520(local_26c,local_12c);
            if (cVar2 == '\0') {
              local_8._0_1_ = 7;
              ~basic_string<>();
              local_8._0_1_ = 6;
              ~basic_string<>();
              local_8._0_1_ = 5;
              ~basic_string<>();
              local_8._0_1_ = 4;
              FUN_00417f10();
              local_8 = CONCAT31(local_8._1_3_,3);
              FUN_0041d0b0();
            }
            else {
              cVar2 = FUN_0041c520(local_26c,local_128);
              if (cVar2 == '\0') {
                local_8._0_1_ = 7;
                ~basic_string<>();
                local_8._0_1_ = 6;
                ~basic_string<>();
                local_8._0_1_ = 5;
                ~basic_string<>();
                local_8._0_1_ = 4;
                FUN_00417f10();
                local_8 = CONCAT31(local_8._1_3_,3);
                FUN_0041d0b0();
              }
              else {
                FUN_004272a0(local_26c,local_124,0x3b);
                bVar1 = std::ios_base::operator!
                                  ((ios_base *)((int)local_26c + *(int *)(local_26c[0] + 4)));
                if (bVar1) {
                  local_8._0_1_ = 7;
                  ~basic_string<>();
                  local_8._0_1_ = 6;
                  ~basic_string<>();
                  local_8._0_1_ = 5;
                  ~basic_string<>();
                  local_8._0_1_ = 4;
                  FUN_00417f10();
                  local_8 = CONCAT31(local_8._1_3_,3);
                  FUN_0041d0b0();
                }
                else {
                  FUN_004272a0(local_26c,local_e8,0x3b);
                  basic_string<>();
                  local_8._0_1_ = 9;
                  FUN_004272a0(local_26c,local_bc,0x3b);
                  local_d0 = FUN_0041c1f0(local_bc,0xffffffff);
                  FUN_004272a0(local_26c,local_bc,0x3b);
                  local_cc = FUN_0041c1f0(local_bc,local_d0);
                  basic_string<>();
                  local_8 = CONCAT31(local_8._1_3_,10);
                  FUN_004272a0(local_26c,local_74,0x3b);
                  local_10c = FUN_0041c300(local_74);
                  FUN_004272a0(local_26c,local_108,0x3b);
                  FUN_0041f830();
                  FUN_004272a0(local_26c,local_74,0x3b);
                  local_f0 = FUN_0041c300(local_74);
                  cVar2 = FUN_0041f890();
                  if (cVar2 == '\0') {
                    if (local_18c != 0) {
                      FUN_0041fcc0(local_150);
                    }
                  }
                  else {
                    cVar2 = FUN_00427270(local_44,"common");
                    if (cVar2 == '\0') {
                      puVar7 = local_150;
                      FUN_00420190(local_44);
                      FUN_0041fcc0(puVar7);
                    }
                    else {
                      FUN_0041fcc0(local_150);
                    }
                  }
                  local_8._0_1_ = 9;
                  ~basic_string<>();
                  local_8._0_1_ = 8;
                  ~basic_string<>();
                  local_8._0_1_ = 7;
                  ~basic_string<>();
                  local_8._0_1_ = 6;
                  ~basic_string<>();
                  local_8._0_1_ = 5;
                  ~basic_string<>();
                  local_8._0_1_ = 4;
                  FUN_00417f10();
                  local_8 = CONCAT31(local_8._1_3_,3);
                  FUN_0041d0b0();
                }
              }
            }
          }
        }
      }
    }
    goto LAB_0041c68b;
  }
  FUN_00426b10(0,0,0);
  local_8._0_1_ = 0xb;
  local_1b0 = FUN_00417fd0(local_180);
  local_8._0_1_ = 0xc;
  local_1ac = local_1b0;
  uVar3 = FUN_0041f870();
  FUN_00426c30(uVar3);
  local_8 = CONCAT31(local_8._1_3_,0xb);
  ~basic_string<>();
  local_1a0 = (byte *)FUN_00426cf0("buttonsystem",&DAT_0087128c,0,0);
  if (local_1a0 == (byte *)0x0) {
    *(undefined4 *)(local_184 + 0x74) = 1;
  }
  else {
    local_194 = &DAT_0087127c;
    local_190 = local_1a0;
    do {
      local_185 = *local_190;
      bVar1 = local_185 < *local_194;
      if (local_185 != *local_194) {
LAB_0041cf0c:
        local_1a8 = -(uint)bVar1 | 1;
        goto LAB_0041cf17;
      }
      if (local_185 == 0) break;
      local_186 = local_190[1];
      bVar1 = local_186 < local_194[1];
      if (local_186 != local_194[1]) goto LAB_0041cf0c;
      local_190 = local_190 + 2;
      local_194 = local_194 + 2;
    } while (local_186 != 0);
    local_1a8 = 0;
LAB_0041cf17:
    local_1b4 = local_1a8;
    local_1a4 = (uint)(local_1a8 != 0);
    *(uint *)(local_184 + 0x74) = local_1a4;
  }
  local_198 = (char *)FUN_00426cf0("buttonsystem","config",0,0);
  if (local_198 == (char *)0x0) {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               (local_184 + 0x2c),"default");
  }
  else {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               (local_184 + 0x2c),local_198);
    uVar3 = FID_conflict_begin(local_1b8);
    FUN_00420350(local_1bc,local_184 + 0x2c);
    cVar2 = FUN_004221b0(uVar3);
    if (cVar2 != '\0') {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 (local_184 + 0x2c),"default");
    }
  }
  local_8._0_1_ = 3;
  FUN_00426bc0();
  local_8._0_1_ = 2;
  FUN_0041d080();
  local_8._0_1_ = 1;
  FUN_004180b0();
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

