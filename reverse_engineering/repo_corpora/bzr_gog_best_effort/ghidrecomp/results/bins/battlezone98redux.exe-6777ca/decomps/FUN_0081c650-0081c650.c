
void FUN_0081c650(void)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar5;
  undefined4 *puVar6;
  undefined1 *puVar7;
  undefined4 uVar8;
  undefined1 *puVar9;
  undefined4 uVar10;
  undefined1 *puVar11;
  undefined *puVar12;
  undefined4 uVar13;
  uint uVar14;
  undefined1 local_248 [176];
  undefined1 local_198 [184];
  undefined1 local_e0 [4];
  undefined1 local_dc [8];
  undefined1 local_d4 [4];
  undefined1 local_d0 [4];
  undefined1 local_cc [4];
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  int *local_bc;
  int *local_b8;
  int local_b4;
  uint local_b0;
  uint local_ac;
  undefined1 local_a6;
  undefined1 local_a5;
  undefined1 local_a4 [12];
  undefined1 local_98 [24];
  undefined1 local_80 [24];
  undefined1 local_68 [24];
  undefined1 local_50 [48];
  undefined1 local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00426a60(&DAT_02cf0000,0);
  iVar2 = FUN_004344a0();
  if (iVar2 == 2) {
    FUN_00426af0("localization_table_mbl.csv");
  }
  else {
    FUN_00426af0("localization_table.csv");
  }
  uVar13 = 1;
  uVar10 = 0x40;
  uVar8 = 1;
  uVar3 = FUN_00417fd0(local_98);
  FUN_0048a460(uVar3,uVar8,uVar10,uVar13);
  ~basic_string<>();
  basic_string<>();
  FUN_0081ce70();
  FUN_004272d0(local_198,local_20);
  while( true ) {
    local_b8 = (int *)FUN_004272d0(local_198,local_20);
    bVar1 = std::ios_base::operator_bool((ios_base *)((int)local_b8 + *(int *)(*local_b8 + 4)));
    if (!bVar1) break;
    iVar2 = FUN_004170c0();
    if ((iVar2 != 0) && (pcVar4 = (char *)FUN_00766f30(0), *pcVar4 != '~')) {
      vector<>();
      FUN_004203f0(local_20,3,1);
      basic_string<>();
      while( true ) {
        local_bc = (int *)FUN_004272a0(local_248,local_50,0x7e);
        bVar1 = std::ios_base::operator_bool((ios_base *)((int)local_bc + *(int *)(*local_bc + 4)));
        if (!bVar1) break;
        FUN_006cae50(local_50);
      }
      FUN_006cf480(0);
      iVar2 = FUN_004170c0();
      if (iVar2 != 0) {
        uVar14 = 0;
        pbVar5 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 FUN_006cf480(0);
        pcVar4 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                 operator[](pbVar5,uVar14);
        if (*pcVar4 == '^') {
          uVar8 = 0xffffffff;
          uVar3 = 1;
          puVar9 = local_80;
          FUN_006cf480(0);
          uVar3 = FUN_0045e1d0(puVar9,uVar3,uVar8);
          FUN_006cf480(0);
          FUN_0045e0f0(uVar3);
          ~basic_string<>();
          local_ac = 1;
          while (uVar14 = FUN_0048a830(), local_ac < uVar14) {
            local_a6 = 10;
            local_a5 = 0x5e;
            puVar9 = &local_a6;
            puVar11 = &local_a5;
            pbVar5 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *
                     )FUN_006cf480(local_ac);
            puVar6 = (undefined4 *)
                     std::
                     basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                     end(pbVar5);
            uVar3 = *puVar6;
            puVar7 = local_d0;
            FUN_006cf480(local_ac);
            puVar6 = (undefined4 *)FID_conflict_begin(puVar7);
            FUN_0081d340(*puVar6,uVar3,puVar11,puVar9);
            local_ac = local_ac + 1;
          }
        }
      }
      FUN_006cf480(0);
      iVar2 = FUN_004170c0();
      if (iVar2 != 0) {
        uVar14 = 0;
        pbVar5 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 FUN_006cf480(0);
        pcVar4 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                 operator[](pbVar5,uVar14);
        if (*pcVar4 == '%') {
          uVar8 = 0xffffffff;
          uVar3 = 1;
          puVar9 = local_68;
          FUN_006cf480(0);
          uVar3 = FUN_0045e1d0(puVar9,uVar3,uVar8);
          FUN_006cf480(0);
          FUN_0045e0f0(uVar3);
          ~basic_string<>();
          local_b0 = 1;
          while (uVar14 = FUN_0048a830(), local_b0 < uVar14) {
            while( true ) {
              uVar3 = 0;
              puVar12 = &DAT_008a1e50;
              FUN_006cf480(local_b0);
              iVar2 = FUN_005871b0(puVar12,uVar3);
              local_b4 = iVar2;
              if (iVar2 == -1) break;
              puVar12 = &DAT_0089c374;
              uVar3 = 1;
              FUN_006cf480(local_b0);
              FUN_0081cd60(iVar2,uVar3,puVar12);
            }
            local_b0 = local_b0 + 1;
          }
        }
      }
      uVar3 = FUN_006cf480(0);
      local_c4 = FUN_0081c5e0(uVar3);
      uVar3 = 1;
      puVar9 = local_cc;
      FID_conflict_begin(local_d4);
      puVar6 = (undefined4 *)FID_conflict_operator_(puVar9,uVar3);
      local_c8 = *puVar6;
      puVar6 = (undefined4 *)FID_conflict_begin(local_e0);
      local_c0 = *puVar6;
      FID_conflict_erase(local_dc,local_c0,local_c8);
      uVar3 = FUN_006cf480(6);
      uVar8 = FUN_006cf480(5);
      swap<>(uVar8,uVar3);
      puVar9 = local_a4;
      FUN_0081cdd0(&local_c4);
      FUN_0048a060(puVar9);
      ~basic_string<>();
      FUN_00417f10();
      FUN_0048a040();
    }
  }
  ~basic_string<>();
  FUN_0041d080();
  FUN_004180b0();
  FUN_0083e885();
  return;
}

