
void __fastcall FUN_005c1b30(float *param_1)

{
  char cVar1;
  float *pfVar2;
  uint uVar3;
  int iVar4;
  float10 fVar5;
  undefined1 local_64 [44];
  float local_38;
  undefined4 *local_34;
  float local_30;
  float local_2c;
  int local_28;
  undefined4 local_24;
  int local_20;
  int local_1c;
  float *local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = param_1;
  pfVar2 = (float *)(**(code **)(*(int *)((int)param_1[4] + 0x18) + 0xc))();
  local_14 = *pfVar2;
  local_10 = pfVar2[1];
  local_c = pfVar2[2];
  local_24 = (**(code **)(*(int *)((int)local_18[4] + 0x18) + 4))();
  local_20 = FUN_00462610();
  if (local_20 != 0) {
    FUN_005c17c0(local_24);
  }
  if (local_18[1] <= 0.0) {
    *(undefined1 *)(local_18 + 2) = 1;
  }
  else {
    fVar5 = (float10)FUN_00822d60();
    local_2c = (float)fVar5;
    local_18[3] = local_18[3] - local_2c;
    if (0.0 < local_18[3] || local_18[3] == 0.0) {
      *(undefined1 *)(local_18 + 2) = 0;
      goto LAB_005c1d43;
    }
    local_18[3] = local_18[3] + local_18[1];
    *(undefined1 *)(local_18 + 2) = 1;
  }
  FUN_005b28e0((double)local_14,(double)local_c,(double)*local_18,local_64);
  local_38 = *local_18 * *local_18;
  while (cVar1 = FUN_00462710(&local_34), cVar1 != '\0') {
    local_1c = FUN_004da060(*local_34);
    if ((((local_1c != 0) && (uVar3 = FUN_0045c4b0(), (uVar3 & 1) == 0)) &&
        (iVar4 = (*(code *)**(undefined4 **)(local_1c + 0x18))(), *(int *)(iVar4 + 0x1c) != 4)) &&
       ((local_28 = FUN_005c1830(), local_28 == 0 || (cVar1 = FUN_005c1850(), cVar1 == '\0')))) {
      (**(code **)(*(int *)(local_1c + 0x18) + 0xc))(local_14,local_10,local_c);
      fVar5 = (float10)FUN_004620b0();
      local_30 = (float)fVar5;
      if (local_30 < local_38) {
        FUN_005c17c0(local_24);
      }
    }
  }
LAB_005c1d43:
  FUN_0083e885();
  return;
}

