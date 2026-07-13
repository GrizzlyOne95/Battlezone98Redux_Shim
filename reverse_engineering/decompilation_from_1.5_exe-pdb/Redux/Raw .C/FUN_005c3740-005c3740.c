
undefined1 __thiscall FUN_005c3740(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined1 local_40;
  char local_3c;
  char local_34;
  char local_30;
  char local_2c;
  char local_28;
  char local_24;
  char local_20;
  char local_1c;
  char local_18;
  undefined4 local_10;
  int local_c;
  char local_5;
  
  local_5 = 1;
  local_c = param_1;
  cVar1 = FUN_004cd360(param_2,param_1 + 0x18,4,"oldhealth");
  local_5 = cVar1 != '\0';
  local_10 = *(undefined4 *)(local_c + 0x1c);
  if (((bool)local_5) && (cVar1 = FUN_004cd1b0(param_2,&local_10,4,"curState"), cVar1 != '\0')) {
    local_18 = '\x01';
  }
  else {
    local_18 = '\0';
  }
  local_5 = local_18;
  local_10 = *(undefined4 *)(local_c + 0x20);
  if ((local_18 == '\0') || (cVar1 = FUN_004cd1b0(param_2,&local_10,4,"nextState"), cVar1 == '\0'))
  {
    local_1c = '\0';
  }
  else {
    local_1c = '\x01';
  }
  local_5 = local_1c;
  if ((local_1c == '\0') ||
     (cVar1 = FUN_004cd1b0(param_2,local_c + 0x24,4,"whoHandle"), cVar1 == '\0')) {
    local_20 = '\0';
  }
  else {
    local_20 = '\x01';
  }
  local_5 = local_20;
  if ((local_20 == '\0') || (cVar1 = FUN_004cf520(param_2,local_c + 0x28,4,"craft"), cVar1 == '\0'))
  {
    local_24 = '\0';
  }
  else {
    local_24 = '\x01';
  }
  local_5 = local_24;
  if ((local_24 == '\0') ||
     (cVar1 = FUN_004cd520(param_2,local_c + 0x2c,0xc,"where"), cVar1 == '\0')) {
    local_28 = '\0';
  }
  else {
    local_28 = '\x01';
  }
  local_5 = local_28;
  if ((local_28 == '\0') ||
     (cVar1 = FUN_004cd520(param_2,local_c + 0x38,0xc,"lastScrap"), cVar1 == '\0')) {
    local_2c = '\0';
  }
  else {
    local_2c = '\x01';
  }
  local_5 = local_2c;
  if ((local_2c == '\0') ||
     (cVar1 = FUN_004cd360(param_2,local_c + 0x44,4,"wait_time"), cVar1 == '\0')) {
    local_30 = '\0';
  }
  else {
    local_30 = '\x01';
  }
  local_5 = local_30;
  if ((local_30 == '\0') ||
     (cVar1 = FUN_004ccf20(param_2,local_c + 0x48,1,"recycle"), cVar1 == '\0')) {
    local_34 = '\0';
  }
  else {
    local_34 = '\x01';
  }
  local_5 = local_34;
  if ((local_34 == '\0') ||
     (cVar1 = FUN_004cd1b0(param_2,local_c + 0x4c,4,&DAT_008757b0), cVar1 == '\0')) {
    local_5 = false;
  }
  else {
    local_5 = true;
  }
  if (((bool)local_5) &&
     (cVar1 = FUN_004cf520(param_2,local_c + 0x58,4,&DAT_00875dcc), cVar1 != '\0')) {
    local_3c = '\x01';
  }
  else {
    local_3c = '\0';
  }
  local_5 = local_3c;
  if ((local_3c == '\0') || (cVar1 = FUN_004617b0(param_2), cVar1 == '\0')) {
    local_40 = 0;
  }
  else {
    local_40 = 1;
  }
  return local_40;
}

