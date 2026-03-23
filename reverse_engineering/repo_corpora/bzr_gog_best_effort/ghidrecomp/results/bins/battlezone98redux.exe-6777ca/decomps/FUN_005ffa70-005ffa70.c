
undefined4 __thiscall FUN_005ffa70(int param_1,undefined4 param_2)

{
  char cVar1;
  uint uVar2;
  undefined1 local_90;
  char local_8c;
  char local_88;
  char local_84;
  char local_80;
  char local_7c;
  undefined4 local_78;
  undefined4 local_74;
  int local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
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
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  char local_5;
  
  local_5 = '\x01';
  local_48 = 0;
  local_c = param_1;
  if (*(int *)(param_1 + 0x104) != 0) {
    local_48 = FUN_004778d0();
  }
  local_78 = 0;
  if (*(int *)(local_c + 0x11c) != 0) {
    local_78 = FUN_004d3470();
  }
  if (local_5 == '\0') {
LAB_005ffafd:
    local_8c = '\0';
  }
  else {
    cVar1 = FUN_004cd1b0(param_2,local_c + 8,4,"curState");
    if (cVar1 == '\0') goto LAB_005ffafd;
    local_8c = '\x01';
  }
  local_5 = local_8c;
  if (local_8c == '\0') {
LAB_005ffb42:
    local_54 = 0;
  }
  else {
    cVar1 = FUN_004cd1b0(param_2,local_c + 0xc,4,"nextState");
    if (cVar1 == '\0') goto LAB_005ffb42;
    local_54 = 1;
  }
  local_5 = (char)local_54;
  if ((char)local_54 == '\0') {
LAB_005ffb81:
    local_1c = 0;
  }
  else {
    cVar1 = FUN_004cf520(param_2,local_c + 0x10,4,&DAT_00886704);
    if (cVar1 == '\0') goto LAB_005ffb81;
    local_1c = 1;
  }
  local_5 = (char)local_1c;
  if ((char)local_1c == '\0') {
LAB_005ffbc0:
    local_74 = 0;
  }
  else {
    cVar1 = FUN_004cd1b0(param_2,local_c + 0x14,4,"himHandle");
    if (cVar1 == '\0') goto LAB_005ffbc0;
    local_74 = 1;
  }
  local_5 = (char)local_74;
  if ((char)local_74 == '\0') {
LAB_005ffbff:
    local_24 = 0;
  }
  else {
    cVar1 = FUN_004ccf20(param_2,local_c + 0x1c,1,"wasInTransition");
    if (cVar1 == '\0') goto LAB_005ffbff;
    local_24 = 1;
  }
  local_5 = (char)local_24;
  if ((char)local_24 == '\0') {
LAB_005ffc3e:
    local_5c = 0;
  }
  else {
    cVar1 = FUN_004cd1b0(param_2,local_c + 0x20,4,"saveState");
    if (cVar1 == '\0') goto LAB_005ffc3e;
    local_5c = 1;
  }
  local_5 = (char)local_5c;
  if ((char)local_5c == '\0') {
LAB_005ffc7d:
    local_2c = 0;
  }
  else {
    cVar1 = FUN_004cd1b0(param_2,local_c + 0x24,4,"saveHandle");
    if (cVar1 == '\0') goto LAB_005ffc7d;
    local_2c = 1;
  }
  local_5 = (char)local_2c;
  if ((char)local_2c == '\0') {
LAB_005ffcbc:
    local_84 = '\0';
  }
  else {
    cVar1 = FUN_004cd520(param_2,local_c + 0x28,0xc,"gotoPoint");
    if (cVar1 == '\0') goto LAB_005ffcbc;
    local_84 = '\x01';
  }
  local_5 = local_84;
  if (local_84 == '\0') {
LAB_005ffcfb:
    local_34 = 0;
  }
  else {
    cVar1 = FUN_004cf520(param_2,local_c + 0x40,4,&DAT_00889c8c);
    if (cVar1 == '\0') goto LAB_005ffcfb;
    local_34 = 1;
  }
  local_5 = (char)local_34;
  if ((char)local_34 == '\0') {
LAB_005ffd3a:
    local_64 = 0;
  }
  else {
    cVar1 = FUN_004cd1b0(param_2,local_c + 0x44,4,"planPoint");
    if (cVar1 == '\0') goto LAB_005ffd3a;
    local_64 = 1;
  }
  local_5 = (char)local_64;
  if ((char)local_64 == '\0') {
LAB_005ffd79:
    local_3c = 0;
  }
  else {
    cVar1 = FUN_004cd360(param_2,local_c + 100,4,"braccelFactor");
    if (cVar1 == '\0') goto LAB_005ffd79;
    local_3c = 1;
  }
  local_5 = (char)local_3c;
  if ((char)local_3c == '\0') {
LAB_005ffdb8:
    local_7c = '\0';
  }
  else {
    cVar1 = FUN_004cd360(param_2,local_c + 0x6c,4,"steerFactor");
    if (cVar1 == '\0') goto LAB_005ffdb8;
    local_7c = '\x01';
  }
  local_5 = local_7c;
  if (local_7c == '\0') {
LAB_005ffdf7:
    local_44 = 0;
  }
  else {
    cVar1 = FUN_004cd360(param_2,local_c + 0x68,4,"strafeFactor");
    if (cVar1 == '\0') goto LAB_005ffdf7;
    local_44 = 1;
  }
  local_5 = (char)local_44;
  if ((char)local_44 == '\0') {
LAB_005ffe36:
    local_6c = 0;
  }
  else {
    cVar1 = FUN_004cd1b0(param_2,local_c + 0x78,4,"avoidSkip");
    if (cVar1 == '\0') goto LAB_005ffe36;
    local_6c = 1;
  }
  local_5 = (char)local_6c;
  if ((char)local_6c == '\0') {
LAB_005ffe77:
    local_4c = 0;
  }
  else {
    cVar1 = FUN_004cd360(param_2,local_c + 0x84,4,"nextStuck");
    if (cVar1 == '\0') goto LAB_005ffe77;
    local_4c = 1;
  }
  local_5 = (char)local_4c;
  if ((char)local_4c == '\0') {
LAB_005ffeb9:
    local_10 = 0;
  }
  else {
    cVar1 = FUN_004cd520(param_2,local_c + 0x88,0xc,"lastStuck");
    if (cVar1 == '\0') goto LAB_005ffeb9;
    local_10 = 1;
  }
  local_5 = (char)local_10;
  if ((char)local_10 == '\0') {
LAB_005ffefb:
    local_14 = 0;
  }
  else {
    cVar1 = FUN_004cd1b0(param_2,local_c + 0x94,4,"stuckState");
    if (cVar1 == '\0') goto LAB_005ffefb;
    local_14 = 1;
  }
  local_5 = (char)local_14;
  if ((char)local_14 == '\0') {
LAB_005fff3c:
    local_18 = 0;
  }
  else {
    cVar1 = FUN_004cd360(param_2,local_c + 0xb0,4,"pitch");
    if (cVar1 == '\0') goto LAB_005fff3c;
    local_18 = 1;
  }
  local_5 = (char)local_18;
  if ((char)local_18 == '\0') {
LAB_005fff7e:
    local_20 = 0;
  }
  else {
    cVar1 = FUN_004cd360(param_2,local_c + 0xf0,4,"blastDist");
    if (cVar1 == '\0') goto LAB_005fff7e;
    local_20 = 1;
  }
  local_5 = (char)local_20;
  if ((char)local_20 == '\0') {
LAB_005fffc0:
    local_28 = 0;
  }
  else {
    cVar1 = FUN_004cd360(param_2,local_c + 0xf4,4,"fireConeX");
    if (cVar1 == '\0') goto LAB_005fffc0;
    local_28 = 1;
  }
  local_5 = (char)local_28;
  if ((char)local_28 == '\0') {
LAB_00600001:
    local_30 = 0;
  }
  else {
    cVar1 = FUN_004cd360(param_2,local_c + 0xf8,4,"fireConeY");
    if (cVar1 == '\0') goto LAB_00600001;
    local_30 = 1;
  }
  local_5 = (char)local_30;
  if ((char)local_30 == '\0') {
LAB_00600043:
    local_38 = 0;
  }
  else {
    cVar1 = FUN_004cd360(param_2,local_c + 0xfc,4,"switchDist");
    if (cVar1 == '\0') goto LAB_00600043;
    local_38 = 1;
  }
  local_5 = (char)local_38;
  if ((char)local_38 == '\0') {
LAB_00600085:
    local_40 = 0;
  }
  else {
    cVar1 = FUN_004cd360(param_2,local_c + 0x100,4,"attackStart");
    if (cVar1 == '\0') goto LAB_00600085;
    local_40 = 1;
  }
  local_5 = (char)local_40;
  if ((char)local_40 == '\0') {
LAB_006000c1:
    local_50 = 0;
  }
  else {
    cVar1 = FUN_004cf520(param_2,&local_48,4,"attackTarget");
    if (cVar1 == '\0') goto LAB_006000c1;
    local_50 = 1;
  }
  local_5 = (char)local_50;
  if ((char)local_50 == '\0') {
LAB_00600103:
    local_58 = 0;
  }
  else {
    cVar1 = FUN_004cd360(param_2,local_c + 0x108,4,"noHitTime");
    if (cVar1 == '\0') goto LAB_00600103;
    local_58 = 1;
  }
  local_5 = (char)local_58;
  if ((char)local_58 == '\0') {
LAB_00600145:
    local_60 = 0;
  }
  else {
    cVar1 = FUN_004cd360(param_2,local_c + 0x110,4,"followDx");
    if (cVar1 == '\0') goto LAB_00600145;
    local_60 = 1;
  }
  local_5 = (char)local_60;
  if ((char)local_60 == '\0') {
LAB_00600186:
    local_68 = 0;
  }
  else {
    cVar1 = FUN_004cd360(param_2,local_c + 0x114,4,"followDz");
    if (cVar1 == '\0') goto LAB_00600186;
    local_68 = 1;
  }
  local_5 = (char)local_68;
  if ((char)local_68 == '\0') {
LAB_006001c8:
    local_70 = 0;
  }
  else {
    cVar1 = FUN_004cd360(param_2,local_c + 0x118,4,"lastStopped");
    if (cVar1 == '\0') goto LAB_006001c8;
    local_70 = 1;
  }
  local_5 = (undefined1)local_70;
  if (local_70 == 0) {
LAB_00600204:
    local_80 = '\0';
  }
  else {
    cVar1 = FUN_004cf520(param_2,&local_78,4,"followTarget");
    if (cVar1 == '\0') goto LAB_00600204;
    local_80 = '\x01';
  }
  uVar2 = 0;
  local_5 = local_80;
  if (local_80 == '\0') {
LAB_00600248:
    local_88 = '\0';
  }
  else {
    uVar2 = FUN_004cd360(param_2,local_c + 0x120,4,"timeOut");
    if ((uVar2 & 0xff) == 0) goto LAB_00600248;
    local_88 = '\x01';
  }
  uVar2 = CONCAT31((int3)(uVar2 >> 8),local_88);
  local_5 = local_88;
  if (local_88 != '\0') {
    uVar2 = FUN_00461c90(param_2);
    uVar2 = uVar2 & 0xff;
    if (uVar2 != 0) {
      local_90 = 1;
      goto LAB_0060028c;
    }
  }
  local_90 = 0;
LAB_0060028c:
  return CONCAT31((int3)(uVar2 >> 8),local_90);
}

