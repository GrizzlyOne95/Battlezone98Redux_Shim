
void __thiscall FUN_0042e130(int param_1,int *param_2,char param_3)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined1 *puVar6;
  undefined1 local_9c [4];
  undefined1 local_98 [4];
  undefined1 local_94 [4];
  undefined1 local_90 [4];
  undefined1 local_8c [4];
  undefined1 local_88 [4];
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined *local_64;
  undefined1 local_5e;
  undefined1 local_5d;
  undefined1 local_5c [8];
  undefined1 local_54 [8];
  undefined4 local_4c;
  undefined1 local_48 [8];
  undefined4 local_40;
  undefined4 local_3c;
  int local_38;
  char local_31;
  undefined1 local_30 [28];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008457e0;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_38 = param_1;
  local_14 = uVar2;
  FUN_00430660(*(undefined1 *)(param_1 + 0x1c));
  local_8 = 0;
  if ((*(char *)(local_38 + 0x1c) != '\0') && (param_3 != '\0')) {
    (**(code **)(*param_2 + 4))(&PTR_DAT_0087152c,uVar2);
  }
  vector<>();
  local_8._0_1_ = 1;
  FUN_00430920(local_48);
  FUN_00431230(local_5e);
  local_31 = '\0';
  if (*(int *)(local_38 + 8) != 0) {
    cVar1 = FUN_00431170(param_2,local_30,*(undefined4 *)(local_38 + 8));
    if (cVar1 == '\0') {
      local_70 = 0xffffffff;
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_004284d0();
      local_8 = 0xffffffff;
      FUN_00430250();
      goto LAB_0042e747;
    }
    local_31 = '\x01';
  }
  puVar3 = (undefined4 *)FUN_0042d8c0(local_94);
  local_3c = *puVar3;
  uVar4 = FID_conflict_begin(local_98);
  cVar1 = FUN_00420f10(uVar4);
  if (cVar1 == '\0') {
    local_78 = 0;
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_004284d0();
    local_8 = 0xffffffff;
    FUN_00430250();
LAB_0042e747:
    ExceptionList = local_10;
    FUN_0083e885();
    return;
  }
  iVar5 = FUN_004305e0();
  if (*(int *)(iVar5 + 4) != 0) {
    if (local_31 != '\0') {
      (**(code **)(*param_2 + 4))(&DAT_00871530);
      (**(code **)(*param_2 + 4))(&DAT_00871530);
    }
    iVar5 = FUN_004305e0();
    cVar1 = FUN_00431170(param_2,local_30,*(undefined4 *)(iVar5 + 4));
    if (cVar1 == '\0') {
      local_74 = 0xffffffff;
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_004284d0();
      local_8 = 0xffffffff;
      FUN_00430250();
      goto LAB_0042e747;
    }
    local_31 = '\0';
  }
  if (local_31 != '\0') {
    (**(code **)(*param_2 + 4))(&DAT_00871530);
    (**(code **)(*param_2 + 4))(&DAT_00871530);
    local_31 = '\0';
  }
  puVar3 = (undefined4 *)FUN_004305e0();
  if (*(char *)*puVar3 != '\0') {
    puVar3 = (undefined4 *)FUN_004305e0();
    cVar1 = FUN_004306d0(*puVar3);
    if (cVar1 == '\0') {
      local_7c = 0xffffffff;
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_004284d0();
      local_8 = 0xffffffff;
      FUN_00430250();
      goto LAB_0042e747;
    }
    (**(code **)(*param_2 + 4))(&DAT_00871534);
    uVar4 = ~<>();
    (**(code **)(*param_2 + 4))(uVar4);
    (**(code **)(*param_2 + 4))(&DAT_00871538);
    (**(code **)(*param_2 + 4))(&DAT_00871530);
  }
  vector<>();
  local_8._0_1_ = 2;
  puVar6 = local_54;
  puVar3 = (undefined4 *)FUN_004305e0(puVar6);
  FUN_004309a0(*puVar3,puVar6);
  FUN_00431230(local_5d);
  puVar3 = (undefined4 *)FUN_0042d8c0(local_8c);
  local_4c = *puVar3;
  uVar4 = FID_conflict_begin(local_88);
  cVar1 = FUN_00420f10(uVar4);
  if (cVar1 == '\0') {
    local_31 = 1;
    local_8 = CONCAT31(local_8._1_3_,1);
    FUN_004284d0();
                    /* WARNING: Subroutine does not return */
    FUN_0042de70();
  }
  vector<>();
  local_8._0_1_ = 3;
  puVar6 = local_5c;
  puVar3 = (undefined4 *)FUN_004305e0(puVar6);
  uVar4 = *puVar3;
  puVar3 = (undefined4 *)FUN_004305e0(uVar4);
  FUN_00430ab0(*puVar3,uVar4,puVar6);
  puVar3 = (undefined4 *)FUN_0042d8c0(local_9c);
  local_40 = *puVar3;
  uVar4 = FID_conflict_begin(local_90);
  cVar1 = FUN_00420f10(uVar4);
  if (cVar1 == '\0') {
    local_8 = CONCAT31(local_8._1_3_,2);
    FUN_004284d0();
                    /* WARNING: Subroutine does not return */
    FUN_0042de70();
  }
  iVar5 = FUN_004305e0();
  if (*(int *)(iVar5 + 4) != 0) {
    (**(code **)(*param_2 + 4))(&DAT_00871530);
    iVar5 = FUN_004305e0();
    cVar1 = FUN_00431170(param_2,local_30,*(undefined4 *)(iVar5 + 4));
    if (cVar1 == '\0') {
      local_84 = 0xffffffff;
      local_8._0_1_ = 2;
      FUN_004284d0();
      local_8._0_1_ = 1;
      FUN_004284d0();
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_004284d0();
      local_8 = 0xffffffff;
      FUN_00430250();
      goto LAB_0042e747;
    }
  }
  puVar3 = (undefined4 *)FUN_004305e0();
  cVar1 = FUN_004306d0(*puVar3);
  if (cVar1 == '\0') {
    local_68 = 0xffffffff;
    local_8._0_1_ = 2;
    FUN_004284d0();
    local_8._0_1_ = 1;
    FUN_004284d0();
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_004284d0();
    local_8 = 0xffffffff;
    FUN_00430250();
    goto LAB_0042e747;
  }
  uVar4 = ~<>();
  (**(code **)(*param_2 + 4))(uVar4);
  puVar3 = (undefined4 *)FUN_004305e0();
  cVar1 = FUN_004306d0(*puVar3);
  if (cVar1 == '\0') {
    local_6c = 0xffffffff;
    local_8._0_1_ = 2;
    FUN_004284d0();
    local_8._0_1_ = 1;
    FUN_004284d0();
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_004284d0();
    local_8 = 0xffffffff;
    FUN_00430250();
    goto LAB_0042e747;
  }
  if (*(char *)(local_38 + 0x1f) == '\0') {
    local_64 = &DAT_00871540;
  }
  else {
    local_64 = &DAT_0087153c;
  }
  (**(code **)(*param_2 + 4))(local_64);
  if (*(char *)(local_38 + 0x1e) != '\0') {
    puVar3 = (undefined4 *)FUN_004305e0();
    cVar1 = FUN_004310e0(*puVar3);
    if (cVar1 != '\0') {
      (**(code **)(*param_2 + 4))("<<<END_OF_TEXT\r\n");
      puVar3 = (undefined4 *)FUN_004305e0();
      cVar1 = FUN_00431170(param_2,local_30,*puVar3);
      if (cVar1 == '\0') {
        local_80 = 0xffffffff;
        local_8._0_1_ = 2;
        FUN_004284d0();
        local_8._0_1_ = 1;
        FUN_004284d0();
        local_8 = (uint)local_8._1_3_ << 8;
        FUN_004284d0();
        local_8 = 0xffffffff;
        FUN_00430250();
        goto LAB_0042e747;
      }
      (**(code **)(*param_2 + 4))("END_OF_TEXT");
      goto LAB_0042e46e;
    }
  }
  uVar4 = ~<>();
  (**(code **)(*param_2 + 4))(uVar4);
LAB_0042e46e:
  (**(code **)(*param_2 + 4))(&DAT_00871530);
                    /* WARNING: Subroutine does not return */
  FUN_0042de70();
}

