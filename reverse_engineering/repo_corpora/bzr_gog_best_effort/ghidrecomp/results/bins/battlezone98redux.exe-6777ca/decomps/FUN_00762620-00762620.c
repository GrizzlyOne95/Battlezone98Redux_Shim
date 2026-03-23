
/* WARNING: Removing unreachable block (ram,0x00762796) */

void FUN_00762620(undefined4 param_1,char param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uStack_ac;
  undefined1 local_9c [4];
  undefined1 local_98 [4];
  undefined1 local_94 [12];
  undefined4 *local_88;
  char *local_84;
  undefined4 *local_80;
  undefined4 local_7c;
  CMFCToolBarComboBoxButton *local_78;
  undefined4 local_74;
  CMFCToolBarComboBoxButton *local_6c;
  undefined4 *local_68;
  char *local_64;
  CMFCToolBarComboBoxButton *local_60;
  char *local_5c;
  char *local_58;
  undefined4 local_54;
  char *local_50;
  undefined4 local_4c;
  char *local_48;
  undefined4 local_44;
  char *local_40;
  undefined4 local_3c;
  uint local_38;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_30 [4];
  undefined4 local_2c;
  undefined4 local_28;
  undefined1 local_24;
  char local_23;
  char local_22;
  char local_20;
  char local_1f;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined4 *local_1c;
  char local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085cec0;
  local_10 = ExceptionList;
  uStack_ac = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_ac;
  ExceptionList = &local_10;
  local_8 = 0;
  local_88 = (undefined4 *)FUN_00422ea0();
  local_28 = *local_88;
  local_2c = *local_1c;
  local_15 = '\x01';
  while (local_48 = (char *)FUN_004242d0(local_28), *local_48 == '\0') {
    local_2c = local_28;
    if (param_2 == '\0') {
      local_58 = (char *)FUN_00422f10(local_28);
      local_84 = (char *)FUN_004241e0(param_3);
      local_60 = (CMFCToolBarComboBoxButton *)FUN_00422f60(&local_31);
      iVar1 = CMFCToolBarComboBoxButton::Compare(local_60,local_84,local_58);
      local_23 = (char)iVar1;
      local_15 = local_23;
    }
    else {
      local_40 = (char *)FUN_004241e0(param_3);
      local_50 = (char *)FUN_00422f10(local_28);
      local_78 = (CMFCToolBarComboBoxButton *)FUN_00422f60(&local_33);
      iVar1 = CMFCToolBarComboBoxButton::Compare(local_78,local_50,local_40);
      local_1f = (char)iVar1;
      local_15 = local_1f == '\0';
      local_38 = (uint)(byte)local_15;
    }
    if (local_15 == '\0') {
      local_68 = (undefined4 *)FUN_004242f0(local_28);
      local_3c = *local_68;
    }
    else {
      local_80 = (undefined4 *)FUN_00417780(local_28);
      local_3c = *local_80;
    }
    local_28 = local_3c;
  }
  _Vector_iterator<>(local_2c,local_1c);
  if (local_15 != '\0') {
    uVar2 = FUN_00420260(local_98);
    local_20 = FUN_004221b0(uVar2);
    if (local_20 != '\0') {
      local_24 = 1;
      local_44 = FUN_00417780(param_3);
      local_4c = FUN_007621f0(local_94,1,local_2c,local_44,param_4);
      FUN_0042c980(local_4c,&local_24);
      FUN_00762973();
      return;
    }
    FUN_00430570();
  }
  local_5c = (char *)FUN_004241e0(param_3);
  local_54 = get();
  local_64 = (char *)FUN_00422f10(local_54);
  local_6c = (CMFCToolBarComboBoxButton *)FUN_00422f60(&local_32);
  iVar1 = CMFCToolBarComboBoxButton::Compare(local_6c,local_64,local_5c);
  local_22 = (char)iVar1;
  if (local_22 == '\0') {
    FUN_004328f0(param_4);
    local_1d = 0;
    FUN_0042c980(local_30,&local_1d);
    FUN_00762973();
    return;
  }
  local_1e = 1;
  local_74 = FUN_00417780(param_3);
  local_7c = FUN_007621f0(local_9c,local_15,local_2c,local_74,param_4);
  FUN_0042c980(local_7c,&local_1e);
  FUN_00762973();
  return;
}

