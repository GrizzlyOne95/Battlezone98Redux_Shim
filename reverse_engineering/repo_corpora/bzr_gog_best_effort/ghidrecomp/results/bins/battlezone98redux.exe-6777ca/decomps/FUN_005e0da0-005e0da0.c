
char FUN_005e0da0(undefined4 param_1)

{
  char cVar1;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int local_18;
  undefined4 local_14;
  int local_10;
  int local_c;
  char local_5;
  
  if (DAT_009173b7 == '\0') {
    local_10 = 0;
    local_5 = '\x01';
    while ((local_10 < 0x10 && (local_5 != '\0'))) {
      local_c = *(int *)(&DAT_00918370 + local_10 * 4);
      local_28 = FUN_005e10b0();
      if ((local_5 == '\0') || (cVar1 = FUN_004cd1b0(param_1,&local_28,4,"curScrap"), cVar1 == '\0')
         ) {
        local_14 = 0;
      }
      else {
        local_14 = 1;
      }
      local_5 = (char)local_14;
      if (((char)local_14 == '\0') ||
         (cVar1 = FUN_004cd1b0(param_1,local_c + 0x170,4,"maxScrap"), cVar1 == '\0')) {
        local_18 = 0;
      }
      else {
        local_18 = 1;
      }
      local_5 = (undefined1)local_18;
      if ((local_18 == 0) ||
         (cVar1 = FUN_004cd1b0(param_1,local_c + 0x174,4,"curPilot"), cVar1 == '\0')) {
        local_1c = 0;
      }
      else {
        local_1c = 1;
      }
      local_5 = (char)local_1c;
      if (((char)local_1c == '\0') ||
         (cVar1 = FUN_004cd1b0(param_1,local_c + 0x178,4,"maxPilot"), cVar1 == '\0')) {
        local_20 = 0;
      }
      else {
        local_20 = 1;
      }
      local_5 = (char)local_20;
      if (((char)local_20 == '\0') ||
         (cVar1 = FUN_004cd290(param_1,local_c + 0x17c,4,"dwAllies"), cVar1 == '\0')) {
        local_24 = 0;
      }
      else {
        local_24 = 1;
      }
      local_10 = local_10 + 1;
      local_5 = (char)local_24;
    }
  }
  else {
    local_5 = '\x01';
  }
  return local_5;
}

