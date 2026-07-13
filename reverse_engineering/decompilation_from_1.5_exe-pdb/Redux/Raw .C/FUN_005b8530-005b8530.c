
void __fastcall FUN_005b8530(int *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  float10 fVar5;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar2 = FUN_00462630(param_1[5]);
  param_1[6] = iVar2;
  if (param_1[6] == 0) {
    param_1[3] = 0xd;
    goto LAB_005b8675;
  }
  puVar3 = (undefined4 *)(**(code **)(*(int *)(param_1[6] + 0x18) + 0xc))();
  local_14 = *puVar3;
  local_10 = puVar3[1];
  local_c = puVar3[2];
  uVar4 = (**(code **)(*(int *)(param_1[4] + 0x18) + 0xc))(&local_14);
  fVar5 = (float10)FUN_00462010(uVar4);
  if ((float)param_1[0x48] == 0.0) {
    if ((float)fVar5 < 2500.0) {
      fVar5 = (float10)FUN_00822da0();
      param_1[0x48] = (int)((float)fVar5 + 30.0);
    }
    FUN_004e7150();
    goto LAB_005b8675;
  }
  if (225.0 <= (float)fVar5) {
LAB_005b85fa:
    fVar5 = (float10)FUN_00822da0();
    if ((float)fVar5 < (float)param_1[0x48] || (float)fVar5 == (float)param_1[0x48]) {
      FUN_004e7150();
      goto LAB_005b8675;
    }
  }
  else {
    cVar1 = FUN_00466d40(&local_14);
    if (cVar1 == '\0') goto LAB_005b85fa;
  }
  param_1[0x55] = 0;
  (**(code **)(*param_1 + 0x3c))();
LAB_005b8675:
  FUN_0083e885();
  return;
}

