
undefined4 FUN_007f3e40(undefined4 param_1,double param_2)

{
  char cVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  float10 fVar5;
  double dVar6;
  double dVar7;
  undefined4 uVar8;
  uint uVar9;
  undefined4 local_44;
  double local_40;
  undefined4 local_38;
  uint local_34;
  undefined4 local_30;
  double local_2c;
  double local_24;
  double local_1c;
  int local_14;
  int local_10;
  int local_c;
  char local_7;
  char local_6;
  char local_5;
  
  uVar3 = SUB84(param_2,0);
  uVar8 = (undefined4)((ulonglong)param_2 >> 0x20);
  local_7 = FUN_006dc8e0(uVar3,uVar8);
  local_6 = '\0';
  local_34 = FUN_007f4930(uVar3,uVar8);
  cVar1 = FUN_007d9780(uVar3,uVar8);
  if (cVar1 != '\0') {
    param_2 = -param_2;
    local_6 = '\x01';
  }
  uVar3 = (undefined4)((ulonglong)param_2 >> 0x20);
  local_c = FUN_007507f0(SUB84(param_2,0),uVar3);
  local_44 = 0x10;
  piVar2 = (int *)_Min_value<>(&local_c,&local_44);
  local_c = *piVar2;
  local_24 = 0.0;
  if (((local_34 & 1) == 0) && (cVar1 = FUN_007f4fd0(SUB84(param_2,0),uVar3), cVar1 == '\0')) {
    dVar6 = param_2;
    __libm_sse2_log10();
    uVar9 = (uint)((ulonglong)dVar6 >> 0x20);
    local_24 = dVar6;
    if (dVar6 <= 0.0) {
      if (param_2 < 1.0) {
        local_14 = FUN_007f4ff0(SUB84(dVar6,0),uVar9 ^ 0x80000000);
        if ((double)local_14 != -local_24) {
          local_14 = local_14 + 1;
        }
        local_24 = (double)-local_14;
        fVar5 = (float10)FUN_007f5020(local_14);
        param_2 = (double)fVar5 * param_2;
      }
    }
    else {
      uVar3 = FUN_007f4ff0(SUB84(dVar6,0),uVar9);
      fVar5 = (float10)FUN_007f5020(uVar3);
      param_2 = param_2 / (double)fVar5;
    }
  }
  fVar5 = (float10)FUN_007f5020(local_c);
  dVar6 = (double)fVar5;
  local_2c = modf(param_2,&local_40);
  local_2c = floor(local_2c * dVar6 + 0.5);
  if (dVar6 <= local_2c) {
    local_2c = floor(local_2c - dVar6);
    local_40 = local_40 + 1.0;
  }
  dVar7 = floor(local_40);
  local_1c = local_2c;
  local_10 = local_c;
  cVar1 = FUN_006dc8e0(SUB84(param_2,0),(int)((ulonglong)param_2 >> 0x20));
  dVar6 = local_1c;
  if (cVar1 == '\0') {
    if (local_1c == 0.0) {
      local_10 = 0;
    }
    else {
      while ((local_10 != 0 &&
             (iVar4 = FUN_007f5040(SUB84(local_1c,0),(int)((ulonglong)local_1c >> 0x20)), iVar4 == 0
             ))) {
        fVar5 = (float10)FUN_007f5070(&local_1c);
        local_1c = (double)fVar5;
        local_10 = local_10 + -1;
      }
    }
    if (local_c != local_10) {
      fVar5 = (float10)FUN_007f5020(local_c - local_10);
      local_1c = dVar6 / (double)fVar5;
    }
  }
  uVar3 = (undefined4)((ulonglong)dVar7 >> 0x20);
  if ((((local_7 != '\0') || (local_6 != '\0')) &&
      (cVar1 = FUN_007f4fd0(SUB84(dVar7,0),uVar3), cVar1 != '\0')) &&
     (cVar1 = FUN_007f4fd0(SUB84(local_1c,0),(int)((ulonglong)local_1c >> 0x20)), cVar1 != '\0')) {
    local_6 = '\0';
    local_7 = '\0';
  }
  local_5 = FUN_007f50a0(param_1,SUB84(dVar7,0),uVar3,local_6,local_7);
  if ((local_5 == '\0') ||
     (cVar1 = FUN_007f5120(param_1,SUB84(local_1c,0),(int)((ulonglong)local_1c >> 0x20),local_c),
     cVar1 == '\0')) {
    local_30 = 0;
  }
  else {
    local_30 = 1;
  }
  local_5 = (char)local_30;
  if (((char)local_30 == '\0') ||
     (cVar1 = FUN_007f5140(param_1,SUB84(local_1c,0),(int)((ulonglong)local_1c >> 0x20),local_10,
                           local_c), cVar1 == '\0')) {
    local_38 = 0;
  }
  else {
    local_38 = 1;
  }
  local_5 = (char)local_38;
  if (((char)local_38 != '\0') && ((local_34 & 1) == 0)) {
    uVar3 = FUN_007f4ff0(SUB84(local_24,0),(int)((ulonglong)local_24 >> 0x20));
    local_38 = FUN_007f5230(param_1,uVar3);
  }
  return local_38;
}

