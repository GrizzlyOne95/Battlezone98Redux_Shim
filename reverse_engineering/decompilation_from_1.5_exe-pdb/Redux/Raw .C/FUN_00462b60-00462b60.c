
void FUN_00462b60(int param_1,undefined4 param_2,float param_3)

{
  char cVar1;
  float *pfVar2;
  float10 fVar3;
  undefined1 local_68 [44];
  float local_3c;
  float local_38;
  undefined4 *local_34;
  float local_30;
  int local_2c;
  float local_28;
  float local_24;
  float local_20;
  int local_1c;
  int local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1c = 0;
  local_20 = 1.0;
  local_2c = FUN_00462550();
  if ((local_2c != 0) && (local_1c = FUN_00462630(local_2c), local_1c != 0)) {
    cVar1 = FUN_00462a70();
    if (cVar1 == '\0') {
      local_1c = 0;
    }
    else {
      fVar3 = (float10)FUN_00822d80();
      local_3c = (float)fVar3;
      local_38 = local_3c;
      fVar3 = (float10)FUN_00462570();
      local_30 = (float)fVar3;
      fVar3 = (float10)FUN_00462a00(local_38 - local_30);
      local_20 = (float)fVar3;
    }
  }
  pfVar2 = (float *)(**(code **)(*(int *)(param_1 + 0x18) + 0xc))();
  local_14 = *pfVar2;
  local_10 = pfVar2[1];
  local_c = pfVar2[2];
  fVar3 = (float10)FUN_00417910(param_2);
  local_28 = (float)fVar3;
  FUN_005b28e0((double)local_14,(double)local_c,(double)local_28,local_68);
  do {
    do {
      cVar1 = FUN_00462710(&local_34);
      if (cVar1 == '\0') goto LAB_00462d37;
      local_18 = FUN_00462630(*local_34);
    } while (((local_18 == 0) || (local_18 == param_1)) || (cVar1 = FUN_00462a70(), cVar1 == '\0'));
    local_24 = param_3;
    if (local_18 == local_1c) {
      local_24 = param_3 * local_20;
    }
    cVar1 = FUN_00462850(param_1,local_18,local_28,local_24,local_20 * 0.25 + 0.75);
  } while (cVar1 == '\0');
LAB_00462d37:
  FUN_0083e885();
  return;
}

