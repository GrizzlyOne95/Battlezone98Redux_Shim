
void FUN_00577eb0(undefined4 param_1,basic_ostream<char,struct_std::char_traits<char>_> *param_2)

{
  char cVar1;
  undefined2 uVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar6;
  uint uVar7;
  undefined4 uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  ushort uVar13;
  undefined2 uVar14;
  undefined4 uVar15;
  code *pcVar16;
  undefined4 uVar17;
  code *pcVar18;
  code *pcVar19;
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  undefined *local_2c;
  undefined *local_28;
  undefined *local_24;
  undefined *local_20;
  undefined *local_1c;
  char *local_18;
  undefined4 local_14;
  undefined4 local_10;
  char *local_c;
  undefined1 local_5;
  
  puVar3 = (undefined4 *)FUN_00420260(local_30);
  local_10 = *puVar3;
  puVar3 = (undefined4 *)FID_conflict_begin(local_34);
  local_14 = *puVar3;
  cVar1 = FUN_00420f10(&local_14);
  if (cVar1 != '\0') {
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(param_2,FUN_0056f740);
  }
  while (cVar1 = FUN_00420f10(&local_14), cVar1 != '\0') {
    iVar4 = FUN_00421ea0();
    local_c = *(char **)(iVar4 + 0x10);
    pcVar18 = FUN_004bc8c0;
    uVar9 = (uint)(byte)local_c[0x68];
    uVar13 = *(ushort *)(local_c + 0x28);
    uVar5 = FUN_004bc590(param_2,param_1,local_c + 0x74,&DAT_00884900,uVar13,&DAT_008848ac,uVar9,
                         &DAT_008848a8);
    uVar5 = FUN_00574730(uVar5);
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar5);
    pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,uVar13);
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590((short)pbVar6);
    pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,uVar9);
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(pbVar6);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,pcVar18);
    local_5 = *(int *)(local_c + 0x24) != 0;
    if (*local_c == local_5) {
      local_18 = " BAD ";
    }
    else {
      local_18 = "     ";
    }
    if (*local_c == '\0') {
      local_1c = &DAT_00884008;
    }
    else {
      local_1c = &DAT_00884010;
    }
    pcVar18 = FUN_004bc8c0;
    uVar2 = FUN_004bc590(param_2,(short)param_1,"\tSpawning: ",local_1c,local_18);
    uVar5 = FUN_004bc590(uVar2);
    uVar5 = FUN_004bc590(uVar5);
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar5);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,pcVar18);
    if (*(int *)(local_c + 8) == 0) {
      local_20 = &DAT_00884848;
    }
    else {
      local_20 = &DAT_00873e10;
    }
    pcVar18 = FUN_004bc8c0;
    uVar7 = FUN_00416410();
    uVar9 = *(uint *)(local_c + 0xc);
    uVar12 = *(uint *)(local_c + 4);
    uVar5 = FUN_004bc590(param_2,param_1,"\tOffset: ",uVar12," Adding: ",local_20,0x4868,uVar9,
                         " Data Items: ");
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar5);
    pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,uVar12);
    uVar5 = FUN_004bc590(pbVar6);
    uVar5 = FUN_004bc590(uVar5);
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar5);
    pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,uVar9);
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(pbVar6);
    pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,uVar7);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,pcVar18);
    pcVar19 = FUN_004bc8c0;
    pcVar16 = FUN_0056f740;
    uVar9 = *(uint *)(local_c + 0x1b0);
    pcVar18 = FUN_00574a10;
    uVar12 = *(uint *)(local_c + 0x4c);
    uVar7 = *(uint *)(local_c + 0x48);
    uVar11 = *(uint *)(local_c + 0x44);
    uVar10 = *(uint *)(local_c + 0x40);
    uVar5 = FUN_004bc590(param_2,param_1,"\tJT: ",uVar10," LT: ",uVar11," NRx: ",uVar7," NTx: ",
                         uVar12,0x4890);
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar5);
    pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,uVar10);
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(pbVar6);
    pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,uVar11);
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(pbVar6);
    pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,uVar7);
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(pbVar6);
    pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,uVar12);
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(pbVar6);
    pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,pcVar18);
    pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,uVar9);
    pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,pcVar16);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,pcVar19);
    uVar9 = *(uint *)(local_c + 0x6c);
    uVar12 = *(uint *)(local_c + 0x70);
    uVar2 = FUN_004bc590(param_2,(short)param_1,"\tKills: ",uVar12," Deaths: ");
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar2);
    pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,uVar12);
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(pbVar6);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,uVar9);
    iVar4 = FUN_004f6a80();
    if (iVar4 == 0) {
      local_24 = &DAT_00884848;
    }
    else {
      local_24 = &DAT_00873e10;
    }
    pcVar18 = FUN_004bc8c0;
    iVar4 = *(int *)(local_c + 0x50);
    uVar2 = FUN_004bc590(param_2,0x4a30,local_24," Flag Index: ");
    uVar5 = FUN_004bc590(uVar2);
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar5);
    pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,iVar4);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,pcVar18);
    uVar5 = *(undefined4 *)(local_c + 100);
    uVar17 = *(undefined4 *)(local_c + 0x60);
    uVar15 = *(undefined4 *)(local_c + 0x5c);
    uVar2 = (undefined2)*(undefined4 *)(local_c + 0x58);
    uVar14 = (undefined2)((uint)*(undefined4 *)(local_c + 0x58) >> 0x10);
    uVar8 = FUN_004bc590(param_2,param_1,"\tSync In At : ",uVar2,uVar15," Sync Out Ack At: ");
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar8);
    pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                       (pbVar6,CONCAT44(uVar15,CONCAT22(uVar14,uVar2)));
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(pbVar6);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
              (pbVar6,CONCAT44(uVar5,uVar17));
    if (local_c[0x8e] == '\0') {
      local_28 = &DAT_00884848;
    }
    else {
      local_28 = &DAT_00873e10;
    }
    if (local_c[0x8c] == '\0') {
      local_2c = &DAT_00884848;
    }
    else {
      local_2c = &DAT_00873e10;
    }
    pcVar18 = FUN_004bc8c0;
    uVar2 = FUN_004bc590(param_2,0x4934,local_2c," Me: ",local_28);
    uVar5 = FUN_004bc590(uVar2);
    uVar5 = FUN_004bc590(uVar5);
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar5);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,pcVar18);
    pcVar18 = FUN_004bc8c0;
    iVar4 = *(int *)(local_c + 0x94);
    uVar5 = FUN_004bc590((short)param_2,param_1,"\tPing History: ");
    pbVar6 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar5);
    pbVar6 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,iVar4);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar6,pcVar18);
    FUN_00422190();
  }
  return;
}

