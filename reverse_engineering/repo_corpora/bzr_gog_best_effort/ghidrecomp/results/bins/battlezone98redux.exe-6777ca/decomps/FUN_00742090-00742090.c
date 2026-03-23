
void FUN_00742090(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_var;
  int local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  int local_58;
  undefined4 local_54;
  undefined4 local_50;
  int local_4c;
  char *local_48;
  undefined1 local_44 [48];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b14b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_00426a60(&DAT_02cf2000,0);
  local_8 = 0;
  uVar2 = extraout_var;
  FUN_00426af0("multi.ini");
  FUN_00426b10(0,0,0);
  local_8._0_1_ = 1;
  local_70 = FUN_00417fd0(local_44);
  local_8._0_1_ = 2;
  local_6c = local_70;
  uVar2 = FUN_0041f870(uVar1,uVar2);
  FUN_00426c30(uVar2);
  local_8 = CONCAT31(local_8._1_3_,1);
  ~basic_string<>();
  local_48 = (char *)FUN_00426cf0("multi","syncJoin",&DAT_00873ef0,0);
  if ((local_48 == (char *)0x0) || (*local_48 != '1')) {
    local_50 = 0;
  }
  else {
    local_50 = 1;
  }
  *(undefined1 *)(param_1 + 0x114) = (undefined1)local_50;
  local_48 = (char *)FUN_00426cf0("multi","commSat",&DAT_00873ef0,0);
  if ((local_48 == (char *)0x0) || (*local_48 != '1')) {
    local_68 = 0;
  }
  else {
    local_68 = 1;
  }
  *(undefined1 *)(param_1 + 0x115) = (undefined1)local_68;
  local_48 = (char *)FUN_00426cf0("multi","barracks",&DAT_00873ef0,0);
  if ((local_48 == (char *)0x0) || (*local_48 != '1')) {
    local_54 = 0;
  }
  else {
    local_54 = 1;
  }
  *(undefined1 *)(param_1 + 0x116) = (undefined1)local_54;
  local_48 = (char *)FUN_00426cf0("multi","barracks",&DAT_00873ef0,0);
  if ((local_48 == (char *)0x0) || (*local_48 != '1')) {
    local_60 = 0;
  }
  else {
    local_60 = 1;
  }
  *(undefined1 *)(param_1 + 0x116) = (undefined1)local_60;
  local_48 = (char *)FUN_00426cf0("multi","sniper",&DAT_00873ef0,0);
  if ((local_48 == (char *)0x0) || (*local_48 != '1')) {
    local_64 = 0;
  }
  else {
    local_64 = 1;
  }
  *(undefined1 *)(param_1 + 0x124) = (undefined1)local_64;
  local_48 = (char *)FUN_00426cf0("multi","splinter",&DAT_00873ef0,0);
  if ((local_48 == (char *)0x0) || (*local_48 != '1')) {
    local_5c = 0;
  }
  else {
    local_5c = 1;
  }
  *(undefined1 *)(param_1 + 300) = (undefined1)local_5c;
  local_48 = (char *)FUN_00426cf0("multi","playerLives",&DAT_0089a8f0,0);
  iVar3 = atoi(local_48);
  *(int *)(param_1 + 0x11c) = iVar3;
  if ((*(int *)(param_1 + 0x11c) == 0) || (5 < *(uint *)(param_1 + 0x11c))) {
    *(undefined4 *)(param_1 + 0x11c) = 2;
  }
  local_48 = (char *)FUN_00426cf0("multi","playerLimit",&DAT_0089a8f0,0);
  iVar3 = atoi(local_48);
  *(int *)(param_1 + 0x120) = iVar3;
  if ((*(uint *)(param_1 + 0x120) < 2) || (0xf < *(uint *)(param_1 + 0x120))) {
    *(undefined4 *)(param_1 + 0x120) = 2;
  }
  local_48 = (char *)FUN_00426cf0("multi","timeLimit",&DAT_00873c74,0);
  local_4c = sscanf(local_48,"%d:%02d",&local_58,&local_74);
  if (local_4c < 1) {
    *(undefined4 *)(param_1 + 0x118) = 0;
  }
  else if (local_4c < 2) {
    *(int *)(param_1 + 0x118) = local_58;
  }
  else {
    *(int *)(param_1 + 0x118) = local_58 * 0x3c + local_74;
  }
  if (300 < *(uint *)(param_1 + 0x118)) {
    *(undefined4 *)(param_1 + 0x118) = 0;
  }
  local_48 = (char *)FUN_00426cf0("multi","killLimit",&DAT_00873c74,0);
  iVar3 = atoi(local_48);
  *(int *)(param_1 + 0x128) = iVar3;
  if (100 < *(uint *)(param_1 + 0x128)) {
    *(undefined4 *)(param_1 + 0x128) = 0;
  }
  local_8 = local_8 & 0xffffff00;
  FUN_00426bc0();
  local_8 = 0xffffffff;
  FUN_004180b0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

