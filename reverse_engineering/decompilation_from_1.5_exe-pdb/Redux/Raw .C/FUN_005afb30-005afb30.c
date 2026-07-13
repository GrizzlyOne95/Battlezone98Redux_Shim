
char __thiscall FUN_005afb30(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  float10 fVar3;
  int local_40;
  int local_3c;
  undefined1 local_38 [4];
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  char local_5;
  
  local_5 = '\x01';
  local_c = param_1;
  if (DAT_00917b20 < 0x3f3) {
    local_5 = FUN_004ceb10(param_2,local_30,4);
  }
  if (DAT_00917b20 != 0x412) {
    cVar1 = FUN_004ceb10(param_2,local_34,4);
    if ((cVar1 == '\0') || (cVar1 = FUN_004ceb10(param_2,local_38,4), cVar1 == '\0')) {
      local_10 = 0;
    }
    else {
      local_10 = 1;
    }
    local_5 = (char)local_10;
  }
  if ((((local_5 == '\0') ||
       (cVar1 = FUN_004cf640(param_2,local_c + 0x310,4,"Producer::powerSource",local_c),
       cVar1 == '\0')) || (cVar1 = FUN_0045c370(param_2,local_c + 0x228,4), cVar1 == '\0')) ||
     ((cVar1 = FUN_004ceb10(param_2,local_c + 0x318,4), cVar1 == '\0' ||
      (cVar1 = FUN_004ceb10(param_2,local_c + 0x31c,4), cVar1 == '\0')))) {
    local_14 = 0;
  }
  else {
    local_14 = 1;
  }
  local_5 = (char)local_14;
  if (DAT_009173b7 != '\0') {
    fVar3 = (float10)FUN_00822da0();
    local_24 = (float)fVar3;
    *(float *)(local_c + 0x31c) = local_24 + *(float *)(*(int *)(local_c + 0xf8) + 0x5f8);
  }
  if (0x3ed < DAT_00917b20) {
    if (((local_5 == '\0') || (cVar1 = FUN_004cf210(param_2,&local_40,8), cVar1 == '\0')) ||
       (cVar1 = FUN_004ceb10(param_2,local_c + 0x304,4), cVar1 == '\0')) {
      local_18 = 0;
    }
    else {
      local_18 = 1;
    }
    local_5 = (char)local_18;
    if (local_40 == 0 && local_3c == 0) {
      *(undefined4 *)(local_c + 0x300) = 0;
    }
    else {
      uVar2 = FUN_004e0f70(local_40,local_3c);
      *(undefined4 *)(local_c + 0x300) = uVar2;
    }
    if (DAT_00917b20 < 0x403) {
      if ((((local_5 == '\0') || (cVar1 = FUN_004ce910(param_2,local_2c,4), cVar1 == '\0')) ||
          (cVar1 = FUN_004ceb10(param_2,local_28,4), cVar1 == '\0')) ||
         ((cVar1 = FUN_004ceb10(param_2,local_28,4), cVar1 == '\0' ||
          (cVar1 = FUN_004ce910(param_2,local_2c,4), cVar1 == '\0')))) {
        local_1c = 0;
      }
      else {
        local_1c = 1;
      }
      local_5 = (char)local_1c;
    }
  }
  if ((DAT_00917b20 < 0x3f3) || (local_5 == '\0')) {
    if (local_5 != '\0') {
      local_5 = FUN_004a7ff0(param_2);
    }
  }
  else {
    local_5 = FUN_004e9fa0(param_2);
  }
  local_20 = *(undefined4 *)(local_c + 0x228);
  switch(local_20) {
  case 0:
    FUN_0062a270(*(undefined4 *)(local_c + 0xf4),1,local_c + 0x314);
    break;
  case 1:
    FUN_0062a270(*(undefined4 *)(local_c + 0xf4),0,local_c + 0x314);
    break;
  case 2:
    *(undefined4 *)(local_c + 0x228) = 1;
    FUN_0062a270(*(undefined4 *)(local_c + 0xf4),0,local_c + 0x314);
    break;
  case 3:
    FUN_0062a270(*(undefined4 *)(local_c + 0xf4),1,local_c + 0x314);
  }
  return local_5;
}

