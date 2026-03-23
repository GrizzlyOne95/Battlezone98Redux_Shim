
char __thiscall FUN_005f2440(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  undefined1 local_6;
  char local_5;
  
  local_5 = '\x01';
  local_c = param_1;
  if (DAT_00917b20 < 0x3e9) goto LAB_005f2582;
  if (DAT_00917b20 != 0x412) {
    cVar1 = FUN_004ceb10(param_2,local_1c,4);
    if (cVar1 == '\0') {
LAB_005f24d6:
      local_10 = 0;
    }
    else {
      cVar1 = FUN_004ceb10(param_2,local_20,4);
      if (cVar1 == '\0') goto LAB_005f24d6;
      cVar1 = FUN_004ceb10(param_2,local_24,4);
      if (cVar1 == '\0') goto LAB_005f24d6;
      cVar1 = FUN_004ceb10(param_2,local_28,4);
      if (cVar1 == '\0') goto LAB_005f24d6;
      local_10 = 1;
    }
    local_5 = (char)local_10;
  }
  if (local_5 == '\0') {
LAB_005f2532:
    local_14 = 0;
  }
  else {
    cVar1 = FUN_0045c370(param_2,local_c + 0x228,4);
    if (cVar1 == '\0') goto LAB_005f2532;
    cVar1 = FUN_004ceb10(param_2,local_c + 0x308,4);
    if (cVar1 == '\0') goto LAB_005f2532;
    local_14 = 1;
  }
  local_5 = (char)local_14;
  if (DAT_00917b20 == 0x412) goto LAB_005f2582;
  if ((char)local_14 == '\0') {
LAB_005f2575:
    local_18 = 0;
  }
  else {
    cVar1 = FUN_004ce5e0(param_2,&local_6,1);
    if (cVar1 == '\0') goto LAB_005f2575;
    local_18 = 1;
  }
  local_5 = (char)local_18;
LAB_005f2582:
  if (local_5 != '\0') {
    local_5 = FUN_004e9fa0(param_2);
  }
  if ((*(int *)(local_c + 0x228) == 2) || (*(int *)(local_c + 0x228) == 1)) {
    FUN_0062a270(*(undefined4 *)(local_c + 0xf4),0,local_c + 0x304);
  }
  else if (*(int *)(local_c + 0x228) == 3) {
    FUN_0062a270(*(undefined4 *)(local_c + 0xf4),1,local_c + 0x304);
  }
  if ((*(int *)(local_c + 0x228) == 2) && (*(int *)(local_c + 0xfc) != 0)) {
    FUN_005f5830();
  }
  if (*(int *)(local_c + 0x228) == 2) {
    FUN_00444ef0(*(undefined4 *)(local_c + 0xf0));
  }
  return local_5;
}

