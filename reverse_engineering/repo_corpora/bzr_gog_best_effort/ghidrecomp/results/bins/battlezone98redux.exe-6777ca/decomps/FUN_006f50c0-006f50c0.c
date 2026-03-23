
void FUN_006f50c0(undefined4 *param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  int unaff_EDI;
  undefined4 *puVar6;
  undefined4 auStack_110 [7];
  undefined4 auStack_f4 [5];
  undefined4 uStack_e0;
  undefined4 *puStack_dc;
  undefined4 *puStack_d8;
  undefined4 *puStack_d4;
  undefined4 local_c8 [7];
  undefined1 local_ac [16];
  undefined4 local_9c [7];
  undefined1 local_80 [28];
  undefined1 local_64 [28];
  char local_48;
  undefined1 local_44 [4];
  undefined1 local_40 [4];
  undefined4 local_3c;
  undefined4 local_38;
  undefined1 local_34 [8];
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 *local_20;
  int local_1c;
  undefined4 local_18;
  undefined4 *local_14;
  int local_10;
  int local_c;
  int local_8;
  
  puStack_d4 = (undefined4 *)0x6f50d3;
  local_10 = eof(unaff_EDI);
  *(int *)(local_8 + 0x20) = param_3;
  local_1c = param_3;
  if (param_3 != 1) {
    puStack_d4 = (undefined4 *)param_2;
    puStack_d8 = (undefined4 *)0x6f52ba;
    FUN_006f5c40();
    puStack_d4 = (undefined4 *)0x6f52c2;
    iVar4 = FUN_00667170();
    if ((iVar4 != 0) || (param_2 == 0)) goto LAB_006f52d3;
  }
  puStack_d4 = (undefined4 *)local_34;
  puStack_d8 = (undefined4 *)0x6f50ff;
  FUN_006f5ba0();
  puStack_d4 = (undefined4 *)local_34;
  puStack_d8 = (undefined4 *)local_80;
  puStack_dc = (undefined4 *)0x6f510c;
  FUN_006f68d0();
  puStack_d4 = *(undefined4 **)(local_8 + 0x24);
  puStack_d8 = (undefined4 *)local_80;
  puStack_dc = local_c8;
  uStack_e0 = 0x6f5126;
  FUN_006f69d0();
  puStack_d4 = (undefined4 *)local_34;
  puStack_d8 = local_9c;
  puStack_dc = (undefined4 *)0x6f5139;
  FUN_006f6950();
  puStack_d4 = (undefined4 *)local_44;
  puStack_d8 = (undefined4 *)0x6f514b;
  puStack_d4 = (undefined4 *)
               std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               end((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   (local_8 + 8));
  puStack_d4 = (undefined4 *)*puStack_d4;
  puStack_d8 = (undefined4 *)local_40;
  puStack_dc = (undefined4 *)0x6f515d;
  puStack_d8 = (undefined4 *)FID_conflict_begin();
  puStack_d8 = (undefined4 *)*puStack_d8;
  puVar5 = local_9c;
  puVar6 = auStack_f4;
  for (iVar4 = 7; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  puVar5 = local_c8;
  puVar6 = auStack_110;
  for (iVar4 = 7; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  FUN_006ff340(local_64);
  puStack_d4 = local_9c;
  puStack_d8 = (undefined4 *)local_64;
  puStack_dc = (undefined4 *)0x6f51a0;
  cVar1 = FUN_006f6a30();
  if ((cVar1 == '\0') || (local_48 == '\0')) {
    puStack_d4 = (undefined4 *)0x6f51ee;
    iVar4 = FUN_006f5b70();
    puStack_d4 = (undefined4 *)0x6f51fb;
    iVar2 = FUN_00477d50();
    if (iVar4 == iVar2) {
      *(int *)(local_8 + 0x24) = local_10;
      local_c = 0;
    }
    else {
      puStack_d4 = local_9c;
      puStack_d8 = (undefined4 *)local_64;
      puStack_dc = (undefined4 *)0x6f5221;
      cVar1 = FUN_006f6a30();
      if (cVar1 == '\0') {
        puStack_d4 = (undefined4 *)local_80;
        puStack_d8 = local_9c;
        puStack_dc = (undefined4 *)0x6f5253;
        uVar3 = FUN_006f6a10();
        *(undefined4 *)(local_8 + 0x24) = uVar3;
      }
      else {
        puStack_d4 = (undefined4 *)local_80;
        puStack_d8 = (undefined4 *)local_64;
        puStack_dc = (undefined4 *)0x6f5238;
        uVar3 = FUN_006f6a10();
        *(undefined4 *)(local_8 + 0x24) = uVar3;
      }
      puStack_d4 = (undefined4 *)0x10000;
      puStack_d8 = *(undefined4 **)(local_8 + 4);
      puStack_dc = (undefined4 *)0x6f526d;
      local_c = FUN_006f5cc0();
    }
  }
  else {
    puStack_d4 = (undefined4 *)local_80;
    puStack_d8 = (undefined4 *)local_64;
    puStack_dc = (undefined4 *)0x6f51bf;
    iVar4 = FUN_006f6a10();
    puStack_d4 = (undefined4 *)0x6f51cf;
    iVar2 = FUN_004170c0();
    *(int *)(local_8 + 0x24) = iVar4 + iVar2;
    local_c = 0;
  }
  if ((param_3 != 0) || (local_c != 0)) {
    puStack_d4 = (undefined4 *)local_8;
    puStack_d8 = (undefined4 *)local_c;
    puStack_dc = (undefined4 *)local_ac;
    uStack_e0 = 0x6f529b;
    puStack_d8 = (undefined4 *)FUN_006f5bf0();
    puStack_dc = (undefined4 *)0x6f52a6;
    FUN_006ff470();
    return;
  }
LAB_006f52d3:
  if (*(int *)(local_8 + 0x24) == local_10) {
    puStack_d4 = (undefined4 *)0x0;
    puStack_d8 = (undefined4 *)0x3;
    puStack_dc = (undefined4 *)0x6f52ed;
    local_14 = (undefined4 *)FUN_006ff4a0();
  }
  else {
    local_3c = *param_1;
    local_38 = param_1[1];
    local_14 = &local_3c;
  }
  local_20 = local_14;
  local_2c = *local_14;
  local_28 = local_14[1];
  puStack_d4 = (undefined4 *)0x6f5322;
  iVar4 = FUN_00667170();
  if ((iVar4 == 0) && (*(int *)(local_8 + 0x24) != local_10)) {
    local_18 = *(undefined4 *)(local_8 + 0x24);
  }
  else {
    local_18 = 0;
  }
  local_24 = local_18;
  puStack_d4 = &local_24;
  puStack_d8 = &local_2c;
  puStack_dc = (undefined4 *)0x6f535c;
  FUN_006fedd0();
  return;
}

