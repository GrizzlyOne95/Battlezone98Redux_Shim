
undefined4 __thiscall FUN_005f9ab0(int param_1,undefined4 param_2)

{
  char cVar1;
  uint uVar2;
  undefined8 local_6c;
  undefined1 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  int local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  undefined4 local_10;
  int local_c;
  undefined1 local_6;
  char local_5;
  
  local_5 = 1;
  local_6c = 0;
  if (*(int *)(param_1 + 0x44) != 0) {
    local_6c = *(undefined8 *)(*(int *)(param_1 + 0x44) + 0x30);
  }
  local_c = param_1;
  cVar1 = FUN_004cd1b0(param_2,param_1 + 0x18,4,"independence");
  local_5 = cVar1 != '\0';
  local_14 = (uint)(byte)local_5;
  local_10 = *(undefined4 *)(local_c + 0x1c);
  if (((bool)local_5) && (cVar1 = FUN_004cd1b0(param_2,&local_10,4,"curState"), cVar1 != '\0')) {
    local_18 = 1;
  }
  else {
    local_18 = 0;
  }
  local_5 = (char)local_18;
  local_10 = *(undefined4 *)(local_c + 0x20);
  if (((char)local_18 == '\0') ||
     (cVar1 = FUN_004cd1b0(param_2,&local_10,4,"nextState"), cVar1 == '\0')) {
    local_1c = 0;
  }
  else {
    local_1c = 1;
  }
  local_5 = (char)local_1c;
  local_10 = *(undefined4 *)(local_c + 0x24);
  if (((char)local_1c == '\0') ||
     (cVar1 = FUN_004cd1b0(param_2,&local_10,4,"saveState"), cVar1 == '\0')) {
    local_20 = 0;
  }
  else {
    local_20 = 1;
  }
  local_5 = (char)local_20;
  if (((char)local_20 == '\0') ||
     (cVar1 = FUN_004cd290(param_2,local_c + 0x28,4,"saveWho"), cVar1 == '\0')) {
    local_24 = 0;
  }
  else {
    local_24 = 1;
  }
  local_5 = (char)local_24;
  if (*(int *)(local_c + 0x24) != 0) {
    if (((char)local_24 == '\0') ||
       (cVar1 = FUN_004cf520(param_2,local_c + 0x2c,4,"saveWhere"), cVar1 == '\0')) {
      local_28 = 0;
    }
    else {
      local_28 = 1;
    }
    local_5 = (char)local_28;
  }
  if ((local_5 == '\0') ||
     (cVar1 = FUN_004cd360(param_2,local_c + 0x30,4,"nextEnemyCheck"), cVar1 == '\0')) {
    local_2c = 0;
  }
  else {
    local_2c = 1;
  }
  local_5 = (char)local_2c;
  if (((char)local_2c == '\0') ||
     (cVar1 = FUN_004cf520(param_2,local_c + 0x34,4,&DAT_00886704), cVar1 == '\0')) {
    local_30 = 0;
  }
  else {
    local_30 = 1;
  }
  local_5 = (char)local_30;
  if (((char)local_30 == '\0') ||
     (cVar1 = FUN_004cf520(param_2,local_c + 0x38,4,&DAT_00875dcc), cVar1 == '\0')) {
    local_34 = 0;
  }
  else {
    local_34 = 1;
  }
  local_5 = (char)local_34;
  if (((char)local_34 == '\0') ||
     (cVar1 = FUN_004cd290(param_2,local_c + 0x3c,4,"whoHandle"), cVar1 == '\0')) {
    local_38 = 0;
  }
  else {
    local_38 = 1;
  }
  local_5 = (char)local_38;
  if (((char)local_38 == '\0') ||
     (cVar1 = FUN_004cf520(param_2,local_c + 0x10,4,"where"), cVar1 == '\0')) {
    local_3c = 0;
  }
  else {
    local_3c = 1;
  }
  local_5 = (char)local_3c;
  local_6 = 0;
  if (((char)local_3c == '\0') ||
     (cVar1 = FUN_004ccf20(param_2,&local_6,1,"release"), cVar1 == '\0')) {
    local_40 = 0;
  }
  else {
    local_40 = 1;
  }
  local_5 = (char)local_40;
  if (((char)local_40 == '\0') ||
     (cVar1 = FUN_004ccf20(param_2,local_c + 0x40,1,"exact"), cVar1 == '\0')) {
    local_44 = 0;
  }
  else {
    local_44 = 1;
  }
  local_5 = (char)local_44;
  if (((char)local_44 == '\0') ||
     (cVar1 = FUN_004cda70(param_2,&local_6c,8,"whatClass"), cVar1 == '\0')) {
    local_48 = 0;
  }
  else {
    local_48 = 1;
  }
  local_5 = (char)local_48;
  if (((char)local_48 == '\0') ||
     (cVar1 = FUN_004ccf20(param_2,local_c + 0x48,1,"isInTransition"), cVar1 == '\0')) {
    local_4c = 0;
  }
  else {
    local_4c = 1;
  }
  local_5 = (char)local_4c;
  if (((char)local_4c == '\0') ||
     (cVar1 = FUN_004ccf20(param_2,local_c + 0x49,1,"wasInTransition"), cVar1 == '\0')) {
    local_50 = 0;
  }
  else {
    local_50 = 1;
  }
  local_5 = (char)local_50;
  if (((char)local_50 == '\0') ||
     (cVar1 = FUN_004cd360(param_2,local_c + 0x4c,4,"waitStart"), cVar1 == '\0')) {
    local_54 = 0;
  }
  else {
    local_54 = 1;
  }
  local_5 = (char)local_54;
  if (((char)local_54 == '\0') ||
     (cVar1 = FUN_004ccf20(param_2,local_c + 0x50,1,"waitDeploy"), cVar1 == '\0')) {
    local_58 = 0;
  }
  else {
    local_58 = 1;
  }
  local_5 = (undefined1)local_58;
  if ((local_58 == 0) ||
     (cVar1 = FUN_004cd360(param_2,local_c + 0x54,4,"waitDeployTime"), cVar1 == '\0')) {
    local_5c = 0;
  }
  else {
    local_5c = 1;
  }
  uVar2 = 0;
  local_5 = (char)local_5c;
  if (((char)local_5c == '\0') ||
     (uVar2 = FUN_004cd360(param_2,local_c + 0x58,4,"timeOut"), (uVar2 & 0xff) == 0)) {
    local_60 = 0;
  }
  else {
    local_60 = 1;
  }
  uVar2 = CONCAT31((int3)(uVar2 >> 8),(char)local_60);
  local_5 = (char)local_60;
  if ((char)local_60 != '\0') {
    uVar2 = FUN_004617b0(param_2);
    uVar2 = uVar2 & 0xff;
    if (uVar2 != 0) {
      local_64 = 1;
      goto LAB_005fa011;
    }
  }
  local_64 = 0;
LAB_005fa011:
  return CONCAT31((int3)(uVar2 >> 8),local_64);
}

