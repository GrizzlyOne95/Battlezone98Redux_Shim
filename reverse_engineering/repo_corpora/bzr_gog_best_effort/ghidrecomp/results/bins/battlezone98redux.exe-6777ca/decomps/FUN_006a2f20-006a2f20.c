
undefined1 __thiscall FUN_006a2f20(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined1 local_28;
  int local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  uint local_10;
  int local_c;
  char local_5;
  
  local_5 = 1;
  local_c = param_1;
  cVar1 = FUN_004cd1b0(param_2,param_1 + 0x18,4,&DAT_00894d28);
  local_5 = cVar1 != '\0';
  local_10 = (uint)(byte)local_5;
  if (((bool)local_5) &&
     (cVar1 = FUN_004cd1b0(param_2,local_c + 0x1c,4,&DAT_00894d34), cVar1 != '\0')) {
    local_14 = 1;
  }
  else {
    local_14 = 0;
  }
  local_5 = (char)local_14;
  if (((char)local_14 == '\0') ||
     (cVar1 = FUN_004cd1b0(param_2,local_c + 0x20,4,&DAT_00894d30), cVar1 == '\0')) {
    local_18 = 0;
  }
  else {
    local_18 = 1;
  }
  local_5 = (char)local_18;
  local_20 = DAT_02c00a94 * DAT_02c00ed8;
  if (((char)local_18 == '\0') ||
     (cVar1 = FUN_004cd1b0(param_2,&local_20,4,&DAT_00894d94), cVar1 == '\0')) {
    local_1c = 0;
  }
  else {
    local_1c = 1;
  }
  local_5 = (char)local_1c;
  if (((char)local_1c == '\0') ||
     (cVar1 = FUN_004cd010(param_2,DAT_009310a8,local_20,"sendPoints"), cVar1 == '\0')) {
    local_5 = '\0';
  }
  else {
    local_5 = '\x01';
  }
  if ((local_5 == '\0') || (cVar1 = FUN_004617b0(param_2), cVar1 == '\0')) {
    local_28 = 0;
  }
  else {
    local_28 = 1;
  }
  return local_28;
}

