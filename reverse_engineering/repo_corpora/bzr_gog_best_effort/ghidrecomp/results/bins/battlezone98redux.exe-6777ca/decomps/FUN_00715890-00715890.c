
/* WARNING: Removing unreachable block (ram,0x00715f05) */
/* WARNING: Removing unreachable block (ram,0x00715c92) */
/* WARNING: Removing unreachable block (ram,0x00715cad) */
/* WARNING: Removing unreachable block (ram,0x00715c9c) */
/* WARNING: Removing unreachable block (ram,0x00715cb7) */

void FUN_00715890(void)

{
  char cVar1;
  undefined2 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar4;
  undefined4 *puVar5;
  undefined4 uStack_26c;
  undefined4 uStack_264;
  undefined1 *puStack_260;
  char *pcStack_25c;
  ushort uVar6;
  int iVar7;
  undefined1 auStack_238 [192];
  undefined4 local_178;
  undefined4 local_174;
  undefined1 *local_170;
  undefined4 local_16c;
  undefined1 *local_168;
  undefined4 local_164;
  undefined1 *local_160;
  undefined1 *local_15c;
  undefined4 local_158;
  undefined4 local_150;
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_130;
  undefined1 *local_12c;
  undefined1 *local_124;
  undefined1 *local_120;
  int local_11c;
  char local_115;
  undefined4 local_114;
  undefined4 local_110;
  char local_109;
  int local_108;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_008580ea;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_006d08b0();
  FUN_00421ec0();
  local_11c = FUN_006cc050();
  FUN_006ab750();
  FUN_00574400();
  local_8._0_1_ = 1;
  if (&stack0x00000000 == (undefined1 *)0x248) {
    local_12c = (undefined1 *)0x0;
  }
  else {
    local_12c = auStack_238;
  }
  pcStack_25c = (char *)0x715953;
  iVar7 = local_11c;
  pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,iVar7);
  local_158 = GetPolicy();
  local_8._0_1_ = 2;
  local_134 = local_158;
  FUN_006d4480();
  local_8._0_1_ = 1;
  ~basic_string<>();
  if (*(int *)(local_108 + 0xa20) == 3) {
    FUN_006d47b0();
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00417f10();
    local_8 = 0xffffffff;
    FUN_006ca8c0();
  }
  else if ((local_11c == 8) || (*(int *)(local_108 + 0xa20) == 1)) {
    if (local_11c == 9) {
      local_109 = '\x01';
      cVar1 = FUN_006caba0();
      if (cVar1 != '\0') {
        FUN_00421ec0();
        pbVar4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 FUN_006cc070();
        local_168 = (undefined1 *)&uStack_264;
        uStack_26c = 0x715a98;
        local_16c = std::
                    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                *)&uStack_264,pbVar4);
        local_15c = (undefined1 *)&uStack_26c;
        local_178 = shared_ptr<>(local_108 + 0x918);
        local_115 = FUN_0071ba20();
        local_109 = local_115;
      }
      if (local_109 != '\0') {
        FUN_00421ec0();
        FUN_006cc070();
        FUN_00720180();
        cVar1 = FUN_006ab7d0();
        if (cVar1 != '\0') {
          pcStack_25c = (char *)0x715b3c;
          FUN_006f90a0();
        }
      }
    }
    else if (local_11c == 10) {
      cVar1 = FUN_006caba0();
      if (cVar1 != '\0') {
        FUN_00421ec0();
        pbVar4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 FUN_006cc070();
        local_170 = (undefined1 *)&uStack_264;
        uStack_26c = 0x715b86;
        local_174 = std::
                    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                *)&uStack_264,pbVar4);
        local_160 = (undefined1 *)&uStack_26c;
        local_164 = shared_ptr<>(local_108 + 0x918);
        FUN_006f2840();
      }
      cVar1 = FUN_006ab7d0();
      if (cVar1 != '\0') {
        FUN_00421ec0();
        FUN_006d70d0();
      }
    }
    else if (local_11c == 8) {
      FUN_006d08b0();
      FUN_00421ec0();
      FUN_006cc070();
      uVar2 = FUN_006bbb00();
      *(undefined2 *)(local_108 + 0x4c0c) = uVar2;
      cVar1 = FUN_006ab7d0();
      if (cVar1 != '\0') {
        basic_string<>();
        local_8._0_1_ = 3;
        FUN_0071b8f0();
        local_8._0_1_ = 1;
        ~basic_string<>();
        if (&stack0x00000000 == (undefined1 *)0x248) {
          local_124 = (undefined1 *)0x0;
        }
        else {
          local_124 = auStack_238;
        }
        uVar6 = *(ushort *)(local_108 + 0x4c0c);
        pcStack_25c = local_124;
        puStack_260 = (undefined1 *)0x715da0;
        pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
        std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,uVar6);
        FUN_004bc590();
        local_14c = GetPolicy();
        local_8._0_1_ = 5;
        local_144 = local_14c;
        FUN_006d46a0();
        local_8._0_1_ = 1;
        ~basic_string<>();
        basic_string<>();
        local_8._0_1_ = 6;
        pcStack_25c = (char *)0x715e31;
        puVar5 = (undefined4 *)FUN_00720a10();
        local_114 = *puVar5;
        local_110 = puVar5[1];
        local_8 = CONCAT31(local_8._1_3_,1);
        ~basic_string<>();
        cVar1 = FUN_006ab7d0();
        if (cVar1 != '\0') {
          pcStack_25c = (char *)0x715e79;
          FUN_006f90a0();
        }
        local_8 = local_8 & 0xffffff00;
        FUN_00417f10();
        local_8 = 0xffffffff;
        FUN_006ca8c0();
        goto LAB_00716236;
      }
      FUN_00421ec0();
      FUN_006cc070();
      pcStack_25c = (char *)0x715ebf;
      local_130 = FUN_006bbc10();
      FUN_0045e0f0();
      ~basic_string<>();
      cVar1 = FUN_006ab7d0();
      if (cVar1 != '\0') {
        FUN_006d47b0();
        basic_string<>();
        local_8._0_1_ = 7;
        pcStack_25c = (char *)0x715f78;
        puVar5 = (undefined4 *)FUN_00720a10();
        local_114 = *puVar5;
        local_110 = puVar5[1];
        local_8 = CONCAT31(local_8._1_3_,1);
        ~basic_string<>();
        cVar1 = FUN_006ab7d0();
        if (cVar1 != '\0') {
          pcStack_25c = (char *)0x715fc0;
          FUN_006f90a0();
        }
        local_8 = local_8 & 0xffffff00;
        FUN_00417f10();
        local_8 = 0xffffffff;
        FUN_006ca8c0();
        goto LAB_00716236;
      }
      if (*(int *)(local_108 + 0xa20) == 1) {
        basic_string<>();
        local_8._0_1_ = 8;
        FUN_0071b8f0();
        local_8._0_1_ = 1;
        ~basic_string<>();
        if (&stack0x00000000 == (undefined1 *)0x248) {
          local_120 = (undefined1 *)0x0;
        }
        else {
          local_120 = auStack_238;
        }
        uVar6 = *(ushort *)(local_108 + 0x4c0c);
        pcStack_25c = "Received close frame with code ";
        puStack_260 = local_120;
        uStack_264 = 0x716077;
        pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590();
        pcStack_25c = (char *)0x716082;
        std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,uVar6);
        pcStack_25c = (char *)0x716088;
        FUN_004bc590();
        FUN_00574730();
        local_140 = GetPolicy();
        local_8._0_1_ = 9;
        local_138 = local_140;
        FUN_006d4480();
        local_8._0_1_ = 1;
        ~basic_string<>();
        local_150 = basic_string<>();
        local_8._0_1_ = 10;
        pcStack_25c = (char *)0x716124;
        local_148 = local_150;
        puVar5 = (undefined4 *)FUN_00720a10();
        local_114 = *puVar5;
        local_110 = puVar5[1];
        local_8._0_1_ = 1;
        ~basic_string<>();
        cVar1 = FUN_006ab7d0();
        if (cVar1 != '\0') {
          pcStack_25c = (char *)0x71616f;
          FUN_006f90a0();
        }
      }
      else if ((*(int *)(local_108 + 0xa20) == 2) && (*(char *)(local_108 + 0x4c38) == '\0')) {
        FUN_006d08b0();
        *(undefined1 *)(local_108 + 0x4c38) = 1;
        if (*(char *)(local_108 + 0x4be0) != '\0') {
          FUN_006ab750();
          FUN_006daf10();
        }
      }
      else {
        FUN_006d47b0();
      }
    }
    else {
      FUN_006d47b0();
    }
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00417f10();
    local_8 = 0xffffffff;
    FUN_006ca8c0();
  }
  else {
    FUN_006d47b0();
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00417f10();
    local_8 = 0xffffffff;
    FUN_006ca8c0();
  }
LAB_00716236:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

