
undefined4 * FUN_0075fd00(undefined4 *param_1,char *param_2)

{
  char cVar1;
  undefined4 uVar2;
  char *pcVar3;
  CMFCToolBarComboBoxButton *this;
  uint uVar4;
  undefined1 local_24 [4];
  undefined1 local_20 [8];
  undefined4 local_18;
  undefined4 *local_14;
  undefined1 local_10 [11];
  undefined1 local_5;
  
  FUN_00760180(local_10,param_2);
  uVar2 = FID_conflict_begin(local_20);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 == '\0') {
    uVar2 = get();
    pcVar3 = (char *)FUN_00422f10(uVar2);
    this = (CMFCToolBarComboBoxButton *)FUN_00422f60(&local_5);
    uVar4 = CMFCToolBarComboBoxButton::Compare(this,param_2,pcVar3);
    if ((uVar4 & 0xff) == 0) {
      local_14 = &local_18;
      goto LAB_0075fd82;
    }
  }
  local_14 = (undefined4 *)FID_conflict_begin(local_24);
LAB_0075fd82:
  *param_1 = *local_14;
  return param_1;
}

