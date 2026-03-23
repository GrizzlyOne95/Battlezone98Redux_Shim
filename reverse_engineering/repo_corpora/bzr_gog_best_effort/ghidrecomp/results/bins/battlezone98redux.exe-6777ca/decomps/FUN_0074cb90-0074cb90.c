
void FUN_0074cb90(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined *puVar6;
  undefined1 local_a0 [4];
  undefined1 local_9c [4];
  undefined1 local_98 [4];
  undefined4 local_94;
  undefined1 local_90 [4];
  undefined4 local_8c;
  undefined1 local_88 [8];
  undefined1 local_80 [4];
  undefined1 local_7c [4];
  undefined4 local_78;
  undefined4 local_74;
  int local_70;
  int local_6c;
  char local_67;
  char local_66;
  char local_65;
  undefined1 local_64 [4];
  uint local_60;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085bd5b;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_60 = 0;
  local_65 = '\x01';
  FUN_00430590(local_14);
  FID_conflict_begin(local_88);
  FUN_00420260(local_64);
  FID_conflict_begin(local_90);
  do {
    cVar1 = FUN_00420f10(local_90);
    if (cVar1 == '\0') {
      uVar2 = FUN_00416410();
      FUN_00740e70(uVar2);
      ExceptionList = local_10;
      FUN_0083e885();
      return;
    }
    uVar2 = FUN_00422150();
    puVar3 = (undefined4 *)FUN_00578c20(local_98,uVar2);
    local_74 = *puVar3;
    puVar6 = &DAT_0260b1c8;
    puVar5 = local_80;
    FUN_00422150(puVar5,&DAT_0260b1c8);
    FUN_00578c20(puVar5,puVar6);
    puVar5 = local_a0;
    FUN_00422150(puVar5);
    uVar2 = FID_conflict_begin(puVar5);
    local_66 = FUN_00420f10(uVar2);
    cVar1 = FUN_00420f10(local_88);
    if (cVar1 == '\0') {
LAB_0074cda0:
      if (local_66 == '\0') {
        basic_string<>("GameVersion");
        local_8 = 0;
        local_60 = local_60 | 1;
        puVar5 = local_2c;
        FUN_00422150(puVar5,PTR_s_2_2_301_008eda3c);
        uVar2 = FUN_0074d310(puVar5);
        cVar1 = FUN_00427270(uVar2);
        if (cVar1 != '\0') goto LAB_0074ce86;
        if (local_65 == '\x01') {
          basic_string<>("GameVersion");
          local_8 = 1;
          local_60 = local_60 | 2;
          local_94 = basic_string<>(PTR_s_0_0_0_008eda38);
          local_8 = 2;
          local_60 = local_60 | 4;
          puVar5 = local_44;
          local_8c = local_94;
          FUN_00422150(puVar5,local_94);
          uVar2 = FUN_0074d310(puVar5);
          cVar1 = FUN_00427310(uVar2);
          if (cVar1 != '\0') goto LAB_0074ce86;
        }
        local_78 = 0;
      }
      else {
LAB_0074ce86:
        local_78 = 1;
      }
      local_67 = (char)local_78;
      local_8 = 1;
      if ((local_60 & 4) != 0) {
        local_60 = local_60 & 0xfffffffb;
        ~basic_string<>();
      }
      local_8 = 0;
      if ((local_60 & 2) != 0) {
        local_60 = local_60 & 0xfffffffd;
        ~basic_string<>();
      }
      local_8 = 0xffffffff;
      if ((local_60 & 1) != 0) {
        local_60 = local_60 & 0xfffffffe;
        ~basic_string<>();
      }
      if (local_67 != '\0') {
        iVar4 = FUN_00422150();
        iVar4 = iVar4 + 0x10;
        uVar2 = FUN_00422150(iVar4);
        FUN_006cc5c0(uVar2);
        FUN_006c3020(iVar4);
      }
    }
    else {
      uVar2 = FUN_00422150();
      FUN_00422150(uVar2);
      cVar1 = FUN_0056f780(uVar2);
      if (cVar1 == '\0') goto LAB_0074cda0;
      local_6c = FUN_00422150();
      local_6c = local_6c + 0x10;
      local_70 = FUN_00422150();
      local_70 = local_70 + 0x10;
      FUN_00578c20(local_7c,&DAT_0260b1c8);
      if (local_66 != '\0') {
        uVar2 = FID_conflict_begin(local_9c);
        cVar1 = FUN_00420f10(uVar2);
        if (cVar1 != '\0') {
          iVar4 = FUN_00422150();
          iVar4 = iVar4 + 0x4c;
          FUN_00422150(iVar4);
          FUN_006ca7f0(iVar4);
        }
      }
      cVar1 = FUN_0056f780(local_70 + 0x18);
      if (cVar1 != '\0') {
        cVar1 = FUN_0056f780(local_6c + 0x18);
        if (cVar1 != '\0') {
          FUN_006ca7f0(local_6c + 0x28);
          *(undefined4 *)(local_70 + 0x34) = *(undefined4 *)(local_6c + 0x34);
        }
      }
      iVar4 = local_70;
      uVar2 = FUN_00422150(local_70);
      FUN_006cc5c0(uVar2);
      FUN_006c3020(iVar4);
    }
    FUN_00428570();
  } while( true );
}

