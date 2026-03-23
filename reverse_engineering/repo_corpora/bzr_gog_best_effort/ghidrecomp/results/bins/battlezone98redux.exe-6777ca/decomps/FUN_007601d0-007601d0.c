
undefined4 __thiscall FUN_007601d0(undefined4 *param_1,char *param_2)

{
  undefined4 *puVar1;
  char *pcVar2;
  char *pcVar3;
  CMFCToolBarComboBoxButton *this;
  uint uVar4;
  undefined4 local_14;
  undefined4 local_c;
  undefined1 local_5;
  
  puVar1 = (undefined4 *)FUN_00422ea0();
  local_c = *puVar1;
  local_14 = *param_1;
  while (pcVar2 = (char *)FUN_004242d0(local_c), *pcVar2 == '\0') {
    pcVar2 = param_2;
    pcVar3 = (char *)FUN_00422f10(local_c);
    this = (CMFCToolBarComboBoxButton *)FUN_00422f60(&local_5);
    uVar4 = CMFCToolBarComboBoxButton::Compare(this,pcVar3,pcVar2);
    if ((uVar4 & 0xff) == 0) {
      local_14 = local_c;
      puVar1 = (undefined4 *)FUN_00417780(local_c);
      local_c = *puVar1;
    }
    else {
      puVar1 = (undefined4 *)FUN_004242f0(local_c);
      local_c = *puVar1;
    }
  }
  return local_14;
}

