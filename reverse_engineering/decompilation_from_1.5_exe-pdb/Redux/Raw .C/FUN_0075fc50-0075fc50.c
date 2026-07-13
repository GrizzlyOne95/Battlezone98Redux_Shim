
int FUN_0075fc50(char *param_1)

{
  char cVar1;
  undefined4 uVar2;
  char *pcVar3;
  CMFCToolBarComboBoxButton *this;
  uint uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  int iVar7;
  char *pcVar8;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined4 local_14;
  undefined4 local_10 [2];
  allocator<char> local_6;
  undefined1 local_5;
  
  FUN_00760180(local_10,param_1);
  uVar2 = FID_conflict_begin(local_18);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 == '\0') {
    uVar2 = get();
    pcVar3 = (char *)FUN_00422f10(uVar2);
    pcVar8 = param_1;
    this = (CMFCToolBarComboBoxButton *)FUN_00422f60(&local_5);
    uVar4 = CMFCToolBarComboBoxButton::Compare(this,pcVar8,pcVar3);
    if ((uVar4 & 0xff) == 0) goto LAB_0075fcef;
  }
  local_14 = local_10[0];
  uVar2 = std::allocator<char>::allocator<char>(&local_6);
  uVar5 = FUN_00427550(local_1c,param_1,uVar2);
  puVar6 = (undefined4 *)FUN_007608d0(local_20,local_14,&DAT_0260b351,uVar5,uVar2);
  local_10[0] = *puVar6;
LAB_0075fcef:
  iVar7 = FUN_00422150();
  return iVar7 + 0x1c;
}

