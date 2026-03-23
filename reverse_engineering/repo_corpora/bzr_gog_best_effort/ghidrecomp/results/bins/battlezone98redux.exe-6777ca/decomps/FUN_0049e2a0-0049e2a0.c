
undefined1 __thiscall FUN_0049e2a0(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined8 local_24;
  undefined1 local_1c;
  undefined4 local_18;
  int local_14;
  uint local_10;
  int local_c;
  char local_5;
  
  local_5 = 1;
  local_24 = 0;
  if (*(int *)(param_1 + 0x150) != 0) {
    local_24 = *(undefined8 *)(*(int *)(param_1 + 0x150) + 0x30);
  }
  local_c = param_1;
  cVar1 = FUN_004cd1b0(param_2,param_1 + 0x14c,4,"buildStage");
  local_5 = cVar1 != '\0';
  local_10 = (uint)(byte)local_5;
  if (((bool)local_5) && (cVar1 = FUN_004cda70(param_2,&local_24,8,"buildCfg"), cVar1 != '\0')) {
    local_14 = 1;
  }
  else {
    local_14 = 0;
  }
  local_5 = (undefined1)local_14;
  if ((local_14 == 0) ||
     (cVar1 = FUN_004cd360(param_2,local_c + 0x154,4,"buildDistSq"), cVar1 == '\0')) {
    local_18 = 0;
  }
  else {
    local_18 = 1;
  }
  local_5 = (char)local_18;
  if (((char)local_18 == '\0') || (cVar1 = FUN_004e5cf0(param_2), cVar1 == '\0')) {
    local_1c = 0;
  }
  else {
    local_1c = 1;
  }
  return local_1c;
}

