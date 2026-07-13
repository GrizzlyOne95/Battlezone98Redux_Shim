
void FUN_00745480(char param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar6;
  ushort uVar7;
  undefined1 *puVar8;
  undefined1 *puVar9;
  undefined1 auStack_148 [160];
  undefined1 local_a8 [16];
  undefined1 local_98 [4];
  undefined1 local_94 [4];
  undefined1 local_90 [4];
  undefined1 local_8c [4];
  undefined4 local_88;
  undefined4 local_84;
  undefined2 *local_80;
  int local_7c;
  undefined1 *local_70;
  int local_6c;
  int *local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b55b;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00422260(local_14);
  local_8 = 0;
  local_7c = FUN_0056f900();
  if (local_7c == 0) {
    local_8 = 0xffffffff;
    FUN_00428210();
    goto LAB_0074574e;
  }
  local_6c = local_7c;
  puVar2 = (undefined4 *)FUN_0042d8c0(local_8c);
  local_60 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_begin(local_94);
  local_88 = *puVar2;
  cVar1 = FUN_00420f10(&local_88);
  if (cVar1 != '\0') {
    iVar3 = FUN_004305e0();
    if (0 < *(int *)(iVar3 + 0x80)) {
      iVar3 = FUN_004305e0();
      if (*(short *)(iVar3 + 0x28) != 0) {
        iVar3 = FUN_004305e0();
        local_80 = (undefined2 *)FUN_007480f0(iVar3 + 8);
        iVar3 = FUN_004305e0();
        *local_80 = *(undefined2 *)(iVar3 + 0x28);
        iVar3 = FUN_004305e0();
        *(undefined4 *)(local_80 + 2) = *(undefined4 *)(iVar3 + 0x80);
      }
    }
                    /* WARNING: Subroutine does not return */
    FUN_0042de70();
  }
  FUN_00574400(3,1);
  local_8 = CONCAT31(local_8._1_3_,1);
  puVar2 = (undefined4 *)FUN_00420260(local_98);
  local_64 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_begin(local_90);
  local_84 = *puVar2;
  while( true ) {
    cVar1 = FUN_00420f10(&local_84);
    if (cVar1 == '\0') break;
    if (&stack0x00000000 == (undefined1 *)0x158) {
      local_70 = (undefined1 *)0x0;
    }
    else {
      local_70 = auStack_148;
    }
    iVar3 = FUN_00421ea0(0x2c);
    iVar3 = *(int *)(iVar3 + 0x14);
    iVar4 = FUN_00421ea0(0x2c);
    uVar7 = *(ushort *)(iVar4 + 0x10);
    uVar5 = FUN_00421ea0(0x2c);
    uVar5 = FUN_0073ba70(local_70,uVar5);
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_006d9650(uVar5);
    pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,uVar7);
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_006d9650(pbVar6);
    pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,iVar3);
    FUN_006d9650(pbVar6);
    FUN_00422190();
  }
  GetPolicy(local_2c);
  local_8._0_1_ = 2;
  if (param_1 == '\0') {
    cVar1 = operator!=<>(local_6c + 0x30,local_2c);
    if (cVar1 != '\0') goto LAB_007456b2;
  }
  else {
LAB_007456b2:
    FID_conflict_operator_(local_2c);
    uVar5 = FUN_0041f870();
    basic_string<>(uVar5);
    local_8._0_1_ = 3;
    basic_string<>("knownPlayers");
    local_8._0_1_ = 4;
    puVar9 = local_5c;
    puVar8 = local_44;
    uVar5 = FUN_0073bcf0(local_a8);
    (**(code **)(*local_68 + 0x1c))(uVar5,puVar8,puVar9);
    local_8._0_1_ = 3;
    ~basic_string<>();
    local_8._0_1_ = 2;
    ~basic_string<>();
  }
  local_8._0_1_ = 1;
  ~basic_string<>();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00417f10();
  local_8 = 0xffffffff;
  FUN_00428210();
LAB_0074574e:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

