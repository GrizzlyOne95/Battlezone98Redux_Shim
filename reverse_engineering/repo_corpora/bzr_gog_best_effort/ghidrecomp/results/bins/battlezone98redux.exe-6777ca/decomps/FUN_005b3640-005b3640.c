
undefined1 __thiscall FUN_005b3640(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined8 local_3c;
  undefined1 local_34;
  undefined4 local_30;
  int local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  uint local_10;
  int local_c;
  undefined1 local_6;
  char local_5;
  
  local_5 = 1;
  local_3c = 0;
  if (*(int *)(param_1 + 0x30) != 0) {
    local_3c = *(undefined8 *)(*(int *)(param_1 + 0x30) + 0x30);
  }
  local_c = param_1;
  cVar1 = FUN_0045c3c0(param_2,param_1 + 0x18,4,"curState");
  local_5 = cVar1 != '\0';
  local_10 = (uint)(byte)local_5;
  if (((bool)local_5) && (cVar1 = FUN_0045c3c0(param_2,local_c + 0x1c,4,"nextState"), cVar1 != '\0')
     ) {
    local_14 = 1;
  }
  else {
    local_14 = 0;
  }
  local_5 = (char)local_14;
  if (((char)local_14 == '\0') ||
     (cVar1 = FUN_004cf520(param_2,local_c + 0x20,4,"craft"), cVar1 == '\0')) {
    local_18 = 0;
  }
  else {
    local_18 = 1;
  }
  local_5 = (char)local_18;
  local_6 = 0;
  if (((char)local_18 == '\0') ||
     (cVar1 = FUN_004ccf20(param_2,&local_6,1,"release"), cVar1 == '\0')) {
    local_1c = 0;
  }
  else {
    local_1c = 1;
  }
  local_5 = (char)local_1c;
  if (((char)local_1c == '\0') ||
     (cVar1 = FUN_004cf520(param_2,local_c + 0x10,4,"where"), cVar1 == '\0')) {
    local_20 = 0;
  }
  else {
    local_20 = 1;
  }
  local_5 = (char)local_20;
  if (((char)local_20 == '\0') ||
     (cVar1 = FUN_004cd1b0(param_2,local_c + 0x24,4,"whoHandle"), cVar1 == '\0')) {
    local_24 = 0;
  }
  else {
    local_24 = 1;
  }
  local_5 = (char)local_24;
  if (((char)local_24 == '\0') ||
     (cVar1 = FUN_004cd360(param_2,local_c + 0x28,4,"lastHit"), cVar1 == '\0')) {
    local_28 = 0;
  }
  else {
    local_28 = 1;
  }
  local_5 = (char)local_28;
  if (((char)local_28 == '\0') ||
     (cVar1 = FUN_004cf520(param_2,local_c + 0x2c,4,&DAT_00875dcc), cVar1 == '\0')) {
    local_2c = 0;
  }
  else {
    local_2c = 1;
  }
  local_5 = (undefined1)local_2c;
  if ((local_2c == 0) || (cVar1 = FUN_004cda70(param_2,&local_3c,8,"classtobuild"), cVar1 == '\0'))
  {
    local_30 = 0;
  }
  else {
    local_30 = 1;
  }
  local_5 = (char)local_30;
  if (((char)local_30 == '\0') || (cVar1 = FUN_004617b0(param_2), cVar1 == '\0')) {
    local_34 = 0;
  }
  else {
    local_34 = 1;
  }
  return local_34;
}

