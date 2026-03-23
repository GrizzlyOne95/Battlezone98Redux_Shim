
void FUN_007a11e0(void)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  undefined4 *puVar9;
  char *pcVar10;
  float10 fVar11;
  float10 fVar12;
  float fVar13;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_250 [8];
  undefined4 uStack_248;
  undefined1 *puStack_244;
  int local_180;
  int local_17c;
  float local_170;
  uint local_158;
  int local_150;
  undefined1 local_8c [96];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00860071;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iVar3 = FUN_007cb0a0();
  FUN_0073a6b0();
  if (iVar3 != -1) {
    piVar4 = (int *)FUN_004200d0();
    iVar3 = *piVar4;
    FUN_00764760();
    FUN_0042d8c0();
    FUN_00764760();
    FID_conflict_begin();
    while (cVar2 = FUN_00420f10(), cVar2 != '\0') {
      iVar5 = FUN_0042de50();
      if (iVar5 == iVar3) {
        FUN_0042da60();
        break;
      }
      FUN_0042da80();
    }
  }
  iVar3 = FUN_007c48b0();
  iVar5 = FUN_007c48b0();
  FUN_007a10c0();
  FUN_00430590();
  FUN_0042d8c0();
  while( true ) {
    FID_conflict_begin();
    cVar2 = FUN_00420f10();
    if (cVar2 == '\0') break;
    iVar6 = FUN_0042de50();
    if (*(char *)(iVar6 + 0xb0) == '\x01') {
      FUN_0041ff90();
      FUN_0041f870();
      puStack_244 = (undefined1 *)0x7a142d;
      FUN_007cabf0();
      iVar6 = FUN_0056f900();
      if (iVar6 != 0) {
        FUN_0056f900();
        cVar2 = FUN_0056f780();
        if (cVar2 != '\0') {
          cVar2 = FUN_00742cf0();
          if (cVar2 != '\0') {
            operator!=<>();
          }
          FUN_007d0ea0();
          FUN_007cafa0();
          FUN_007cafa0();
          bVar1 = false;
          FUN_0042d8c0();
          FID_conflict_begin();
          local_150 = 0;
          while (cVar2 = FUN_00420f10(), cVar2 != '\0') {
            iVar6 = FUN_0042de50();
            FUN_0041f870();
            puStack_244 = (undefined1 *)0x7a15a0;
            FUN_007cabf0();
            cVar2 = FUN_0073a900();
            if ((cVar2 != '\0') && (cVar2 = FUN_0056f780(), cVar2 != '\0')) {
              FUN_007cafa0();
              bVar1 = true;
            }
            FUN_007c48b0();
            iVar7 = FUN_007c48b0();
            uVar8 = FUN_007cb5a0();
            if ((uint)(local_150 - iVar7) < uVar8) {
              FUN_0056f8b0();
              cVar2 = FUN_0056f780();
              if (cVar2 != '\0') {
                puVar9 = (undefined4 *)FUN_004200d0();
                (**(code **)(*(int *)*puVar9 + 0x24))();
              }
              if (*(char *)(iVar6 + 0x44) == '\x01') {
                puVar9 = (undefined4 *)FUN_004200d0();
                (**(code **)(*(int *)*puVar9 + 0x24))();
              }
            }
            local_150 = local_150 + 1;
            FUN_0042da80();
          }
          if ((!bVar1) && (cVar2 = FUN_0073a900(), cVar2 != '\0')) {
            FUN_0056f7e0();
          }
        }
      }
    }
    else {
      FUN_0041ff90();
      FUN_0041f870();
      basic_string<>();
      local_8 = 0;
      local_170 = 0.0;
      local_158 = 0;
      while( true ) {
        FUN_0041f870();
        fVar11 = (float10)FUN_00689cb0();
        fVar12 = (float10)FUN_007ca700();
        fVar13 = (float)fVar11 * (float)fVar12;
        fVar11 = (float10)FUN_007d3ec0();
        if ((((double)fVar11 * 0.4 <= (double)fVar13) || (fVar13 <= local_170)) ||
           (local_158 = local_158 + 1, 200 < local_158)) break;
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  (local_2c," ");
        local_170 = fVar13;
      }
      FUN_00769eb0();
      local_8._0_1_ = 1;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (abStack_250,
                 (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 (iVar6 + 0xdc));
      local_8._0_1_ = 2;
      FUN_00764770();
      local_8 = CONCAT31(local_8._1_3_,1);
      FUN_007528e0();
      FUN_00449810();
      local_158 = 0;
      while( true ) {
        FUN_0041f870();
        fVar11 = (float10)FUN_00689cb0();
        fVar12 = (float10)FUN_007ca700();
        fVar13 = (float)fVar11 * (float)fVar12;
        fVar11 = (float10)FUN_007d3ec0();
        if ((((double)fVar11 * 0.8 <= (double)fVar13) || (fVar13 <= local_170)) ||
           (local_158 = local_158 + 1, 200 < local_158)) break;
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  (local_2c," ");
        local_170 = fVar13;
      }
      basic_string<>();
      local_8._0_1_ = 3;
      piVar4 = (int *)FUN_00764760();
      pcVar10 = (char *)(**(code **)(*piVar4 + 0x2c))();
      local_8._0_1_ = 1;
      ~basic_string<>();
      puStack_244 = (undefined1 *)0x7a1a67;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (local_2c,pcVar10);
      puStack_244 = (undefined1 *)0x7a1a74;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (local_2c,"/");
      puStack_244 = local_8c;
      uStack_248 = 0x7a1a8d;
      FUN_0073b940();
      local_8._0_1_ = 4;
      puStack_244 = (undefined1 *)0x7a1ab5;
      FUN_00449810();
      local_8._0_1_ = 1;
      ~basic_string<>();
      puStack_244 = (undefined1 *)0x7a1ad1;
      basic_string<>();
      local_8._0_1_ = 5;
      piVar4 = (int *)FUN_00764760();
      puStack_244 = (undefined1 *)(iVar6 + 0x10);
      uStack_248 = 0x7a1b01;
      pcVar10 = (char *)(**(code **)(*piVar4 + 0x2c))();
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 (iVar6 + 0x130),pcVar10);
      local_8 = CONCAT31(local_8._1_3_,1);
      ~basic_string<>();
      cVar2 = operator!=<>();
      if (cVar2 != '\0') {
        FID_conflict_operator_();
      }
      FUN_0041f870();
      puStack_244 = (undefined1 *)0x7a1b80;
      FUN_007cabf0();
      cVar2 = FUN_0073a900();
      if ((cVar2 != '\0') && (cVar2 = FUN_0056f780(), cVar2 != '\0')) {
        FUN_007cafa0();
      }
      local_8 = local_8 & 0xffffff00;
      FUN_00753670();
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    FUN_0042da80();
  }
  for (local_180 = 0; local_180 < iVar3; local_180 = local_180 + 1) {
    FUN_007cb540();
  }
  for (local_17c = 0; local_17c < iVar5; local_17c = local_17c + 1) {
    FUN_007cb540();
  }
  FUN_007a1e20();
  iVar3 = FUN_0056f900();
  if (iVar3 != 0) {
    FUN_0056f900();
    cVar2 = FUN_00427270();
    if (cVar2 != '\0') {
      FUN_0056f900();
      FID_conflict_begin();
      while( true ) {
        FID_conflict_end();
        cVar2 = FID_conflict_operator__();
        if (cVar2 == '\0') break;
        FUN_00421ec0();
        cVar2 = FUN_00427270();
        if (cVar2 != '\0') {
          FUN_0073b9a0();
        }
        FUN_00421ee0();
      }
      FUN_0056f900();
      cVar2 = FUN_0073ba10();
      if (cVar2 != '\0') {
        FUN_00740a90();
        basic_string<>();
        local_8 = 6;
        FUN_00741990();
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

