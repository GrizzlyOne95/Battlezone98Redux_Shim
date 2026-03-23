
void __thiscall FUN_004a7ff0(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  char local_6c;
  char local_68;
  char local_64;
  char local_60;
  undefined1 local_5c [4];
  int local_58;
  char local_51;
  undefined1 local_50 [72];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_58 = param_1;
  if (DAT_00917b20 < 0x3fb) {
    cVar1 = FUN_004ce910(param_2,local_5c,4);
    if (cVar1 == '\0') {
LAB_004a80d3:
      local_60 = '\0';
    }
    else {
      cVar1 = FUN_004ce910(param_2,local_5c,4);
      if (cVar1 == '\0') goto LAB_004a80d3;
      cVar1 = FUN_004ce910(param_2,local_5c,4);
      if (cVar1 == '\0') goto LAB_004a80d3;
      cVar1 = FUN_004ce910(param_2,local_5c,4);
      if (cVar1 == '\0') goto LAB_004a80d3;
      cVar1 = FUN_004ce910(param_2,local_5c,4);
      if (cVar1 == '\0') goto LAB_004a80d3;
      cVar1 = FUN_004ce910(param_2,local_5c,4);
      if (cVar1 == '\0') goto LAB_004a80d3;
      cVar1 = FUN_004ced10(param_2,local_50,0x48);
      if (cVar1 == '\0') goto LAB_004a80d3;
      local_60 = '\x01';
    }
    local_51 = local_60;
  }
  else {
    local_51 = '\x01';
  }
  if (DAT_00917b20 < 0x404) {
    *(undefined4 *)(local_58 + 0x22c) = 0;
  }
  else {
    if (local_51 == '\0') {
LAB_004a8122:
      local_6c = '\0';
    }
    else {
      cVar1 = FUN_004ce910(param_2,local_58 + 0x22c,4);
      if (cVar1 == '\0') goto LAB_004a8122;
      local_6c = '\x01';
    }
    local_51 = local_6c;
  }
  if (DAT_00917b20 < 2000) goto LAB_004a8212;
  if (DAT_00917b20 < 0x7d2) {
    if (local_51 == '\0') {
LAB_004a818a:
      local_68 = '\0';
    }
    else {
      cVar1 = FUN_004ceb10(param_2,local_58 + 0x294,4);
      if (cVar1 == '\0') goto LAB_004a818a;
      local_68 = '\x01';
    }
    local_51 = local_68;
  }
  if (local_51 == '\0') {
LAB_004a8205:
    local_64 = '\0';
  }
  else {
    cVar1 = FUN_0045c370(param_2,local_58 + 0x298,4);
    if (cVar1 == '\0') goto LAB_004a8205;
    cVar1 = FUN_004ceb10(param_2,local_58 + 0x29c,4);
    if (cVar1 == '\0') goto LAB_004a8205;
    cVar1 = FUN_004ceb10(param_2,local_58 + 0x2a0,4);
    if (cVar1 == '\0') goto LAB_004a8205;
    local_64 = '\x01';
  }
  local_51 = local_64;
LAB_004a8212:
  if (local_51 != '\0') {
    local_51 = FUN_004dd370(param_2);
  }
  if ((*(int *)(local_58 + 0x220) == 0) && (*(int *)(local_58 + 0xfc) == 0)) {
    uVar2 = (**(code **)(*(int *)(local_58 + 0x18) + 0x30))();
    *(undefined4 *)(local_58 + 0x220) = uVar2;
  }
  else if ((*(int *)(local_58 + 0x220) != 0) &&
          ((*(int *)(local_58 + 0xfc) != 0 &&
           (*(int *)(*(int *)(local_58 + 0xf8) + 0x14) != 0x54554700)))) {
    *(undefined4 *)(local_58 + 0x220) = 0;
  }
  if (*(float *)(local_58 + 0x200) <= 0.0 && *(float *)(local_58 + 0x200) != 0.0) {
    *(uint *)(*(int *)(local_58 + 0xf4) + 0x14) =
         *(uint *)(*(int *)(local_58 + 0xf4) + 0x14) | 0x200;
  }
  FUN_0083e885();
  return;
}

