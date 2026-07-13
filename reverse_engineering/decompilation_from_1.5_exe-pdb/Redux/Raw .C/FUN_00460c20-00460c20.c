
undefined4 __thiscall FUN_00460c20(int *param_1,undefined4 param_2)

{
  char cVar1;
  uint uVar2;
  int *local_30;
  int local_2c;
  char *local_28;
  char local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int local_18;
  int local_14;
  char *local_10;
  int *local_c;
  undefined1 local_6;
  char local_5;
  
  if (*param_1 == 0) {
    local_18 = 0;
  }
  else {
    local_10 = (char *)*param_1;
    local_28 = local_10 + 1;
    do {
      cVar1 = *local_10;
      local_10 = local_10 + 1;
    } while (cVar1 != '\0');
    local_2c = (int)local_10 - (int)local_28;
    local_6 = 0;
    local_18 = local_2c;
  }
  local_14 = local_18;
  local_30 = param_1;
  local_c = param_1;
  uVar2 = FUN_004ccd10(param_2,"[AiPath]");
  if ((uVar2 & 0xff) == 0) {
LAB_00460cb7:
    local_1c = 0;
  }
  else {
    uVar2 = FUN_004cf520(param_2,&local_30,4,"old_ptr");
    if ((uVar2 & 0xff) == 0) goto LAB_00460cb7;
    local_1c = 1;
  }
  uVar2 = CONCAT31((int3)(uVar2 >> 8),(char)local_1c);
  local_5 = (char)local_1c;
  if ((char)local_1c == '\0') goto LAB_00460dc9;
  if ((char)local_1c == '\0') {
LAB_00460cff:
    local_20 = 0;
  }
  else {
    uVar2 = FUN_004cd1b0(param_2,&local_14,4,&DAT_00874054);
    if ((uVar2 & 0xff) == 0) goto LAB_00460cff;
    local_20 = 1;
  }
  uVar2 = CONCAT31((int3)(uVar2 >> 8),(char)local_20);
  local_5 = (char)local_20;
  if ((char)local_20 == '\0') goto LAB_00460dc9;
  if (0 < local_14) {
    local_5 = FUN_004cce90(param_2,*local_c,local_14,"label");
  }
  uVar2 = 0;
  if (local_5 == '\0') goto LAB_00460dc9;
  cVar1 = FUN_004cd1b0(param_2,local_c + 1,4,"pointCount");
  if (cVar1 == '\0') {
LAB_00460dbc:
    local_24 = '\0';
  }
  else {
    cVar1 = FUN_004cd670(param_2,local_c[2],local_c[1] << 3,"points");
    if (cVar1 == '\0') goto LAB_00460dbc;
    cVar1 = FUN_0045c3c0(param_2,local_c + 4,4,"pathType");
    if (cVar1 == '\0') goto LAB_00460dbc;
    local_24 = '\x01';
  }
  uVar2 = 0;
  local_5 = local_24;
LAB_00460dc9:
  return CONCAT31((int3)(uVar2 >> 8),local_5);
}

