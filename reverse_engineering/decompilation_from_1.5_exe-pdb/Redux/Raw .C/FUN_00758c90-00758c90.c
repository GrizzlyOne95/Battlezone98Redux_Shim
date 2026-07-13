
void FUN_00758c90(byte *param_1,uint param_2,undefined4 param_3)

{
  char cVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar2;
  undefined4 uVar3;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar4;
  undefined4 *puVar5;
  int iVar6;
  uint uVar7;
  code *pcVar8;
  code *pcVar9;
  ushort uVar10;
  basic_ostream<char,struct_std::char_traits<char>_> local_1e0 [160];
  undefined1 local_140 [16];
  undefined1 local_130 [32];
  basic_ostream<char,struct_std::char_traits<char>_> local_110 [160];
  undefined1 local_70 [4];
  undefined1 local_6c [4];
  uint local_68;
  basic_ostream<char,struct_std::char_traits<char>_> *local_64;
  basic_ostream<char,struct_std::char_traits<char>_> *local_60;
  basic_ostream<char,struct_std::char_traits<char>_> *local_5c;
  basic_ostream<char,struct_std::char_traits<char>_> *local_58;
  basic_ostream<char,struct_std::char_traits<char>_> *local_54;
  undefined4 local_50;
  basic_ostream<char,struct_std::char_traits<char>_> *local_4c;
  basic_ostream<char,struct_std::char_traits<char>_> *local_48;
  basic_ostream<char,struct_std::char_traits<char>_> *local_44;
  basic_ostream<char,struct_std::char_traits<char>_> *local_40;
  int *local_3c;
  basic_ostream<char,struct_std::char_traits<char>_> *local_38;
  int local_34;
  undefined1 local_2d;
  int local_2c;
  undefined1 local_25;
  int local_24;
  uint local_20;
  uint local_1c;
  undefined1 local_18;
  undefined1 local_17;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c846;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_24 = FUN_00764760(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (DAT_00917f6c != 0) {
    local_2c = 0;
    local_34 = 0;
    if (local_24 != 0) {
      local_2c = FUN_0073bd10();
      local_34 = FUN_00746690(param_3);
    }
    FUN_00574400(3,1);
    local_8 = 0;
    if (&stack0x00000000 == (undefined1 *)0x120) {
      local_4c = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
    }
    else {
      local_4c = local_110;
    }
    FUN_004bc590(local_4c,"RX SRC ");
    if (local_2c == 0) {
      if (&stack0x00000000 == (undefined1 *)0x120) {
        local_44 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
      }
      else {
        local_44 = local_110;
      }
      FUN_004bc590(local_44,&DAT_0089b76c);
    }
    else {
      if (&stack0x00000000 == (undefined1 *)0x120) {
        local_54 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
      }
      else {
        local_54 = local_110;
      }
      uVar10 = *(ushort *)(local_2c + 0x28);
      pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)
               FUN_004bc590(local_54,&DAT_0088d764);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,uVar10);
    }
    if (&stack0x00000000 == (undefined1 *)0x120) {
      local_5c = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
    }
    else {
      local_5c = local_110;
    }
    FUN_004bc590(local_5c," DST ");
    if (local_34 == 0) {
      if (&stack0x00000000 == (undefined1 *)0x120) {
        local_64 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
      }
      else {
        local_64 = local_110;
      }
      FUN_004bc590(local_64,&DAT_0089b76c);
    }
    else {
      if (&stack0x00000000 == (undefined1 *)0x120) {
        local_38 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
      }
      else {
        local_38 = local_110;
      }
      uVar10 = *(ushort *)(local_34 + 0x28);
      pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)
               FUN_004bc590(local_38,&DAT_0088d764);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,uVar10);
    }
    if (&stack0x00000000 == (undefined1 *)0x120) {
      local_60 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
    }
    else {
      local_60 = local_110;
    }
    uVar3 = FUN_006dc270(&local_25,0x30);
    pcVar9 = FUN_006ab840;
    pcVar8 = FUN_00574a10;
    pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)
             FUN_004bc590(local_60," Packet: ",FUN_00574a10,FUN_006ab840,uVar3);
    pbVar2 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pcVar8);
    pbVar2 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pcVar9);
    FUN_006dc290(pbVar2);
    for (local_1c = 0; local_1c < param_2; local_1c = local_1c + 1) {
      if (&stack0x00000000 == (undefined1 *)0x120) {
        local_58 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
      }
      else {
        local_58 = local_110;
      }
      uVar7 = (uint)param_1[local_1c];
      uVar3 = std::setw(CONCAT44(2,local_130));
      pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_006db8a0(local_58,uVar3);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,uVar7);
    }
    pcVar8 = FUN_004bc8c0;
    pbVar2 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                       (local_110,FUN_0056f740);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pcVar8);
    pbVar4 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
    FUN_0081e820();
    pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pbVar4);
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  *(uint *)(local_14 + 0x28) = *(int *)(local_14 + 0x28) + param_2;
  *(int *)(local_14 + 0x24) = *(int *)(local_14 + 0x24) + 1;
  if (param_2 != 0) {
    local_68 = (uint)*param_1;
    puVar5 = (undefined4 *)FUN_00753a00(local_70,&local_68);
    local_50 = *puVar5;
    if ((*param_1 == 0) && (param_1[1] == 0)) {
      local_18 = 0;
      local_17 = 1;
      FUN_00759710(param_3,&local_18,2,1);
    }
    uVar3 = FID_conflict_begin(local_6c);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') {
      if (*(int *)(local_14 + 0x34) == 0) {
        FUN_00574400(3,1);
        local_8 = 1;
        if (&stack0x00000000 == (undefined1 *)0x1f0) {
          local_40 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
        }
        else {
          local_40 = local_1e0;
        }
        FUN_004bc590(local_40,"Unhandled P2P Data: ");
        std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(local_1e0,FUN_00574a10);
        if (&stack0x00000000 == (undefined1 *)0x1f0) {
          local_48 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
        }
        else {
          local_48 = local_1e0;
        }
        uVar3 = FUN_006dc270(&local_2d,0x30);
        FUN_006dc290(local_48,uVar3);
        for (local_20 = 0; local_20 < param_2; local_20 = local_20 + 1) {
          uVar7 = (uint)param_1[local_20];
          uVar3 = std::setw(CONCAT44(2,local_140));
          pbVar2 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                             (local_1e0,FUN_006ab840);
          pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_006db8a0(pbVar2,uVar3);
          std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,uVar7);
        }
        std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(local_1e0,FUN_004bc8c0);
        pcVar8 = FUN_004bc8c0;
        pbVar4 = (basic_streambuf<char,struct_std::char_traits<char>_> *)FUN_00583e30();
        FUN_0081e820();
        pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_0081e660();
        pbVar2 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pbVar4);
        std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pcVar8);
        local_8 = 0xffffffff;
        FUN_00417f10();
      }
      else {
        (**(code **)(**(int **)(local_14 + 0x34) + 4))(local_14,param_3,param_1,param_2);
      }
    }
    else {
      iVar6 = FUN_00421ea0();
      local_3c = *(int **)(iVar6 + 4);
      (**(code **)(*local_3c + 4))(local_14,param_3,param_1,param_2);
    }
  }
  ExceptionList = local_10;
  return;
}

