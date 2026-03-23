
void FUN_005c9fc0(float *param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  undefined1 local_4c [44];
  undefined4 *local_20;
  undefined4 local_1c;
  int local_18;
  float local_14;
  float local_10;
  int local_c;
  int local_8;
  
  local_14 = 1e+30;
  local_18 = 0;
  local_1c = 0x43e10000;
  FUN_005b28e0((double)*param_1,(double)param_1[2],0x407c200000000000,local_4c);
  if (param_2 == 0) {
    param_2 = FUN_00417c70();
  }
  while (cVar1 = FUN_00462710(&local_20), cVar1 != '\0') {
    local_8 = FUN_00462630(*local_20);
    if ((local_8 != 0) && (local_8 != param_2)) {
      uVar2 = (**(code **)(*(int *)(local_8 + 0x18) + 4))();
      cVar1 = FUN_004db600(uVar2);
      if (cVar1 != '\0') {
        uVar2 = FUN_004625b0();
        cVar1 = FUN_004db600(uVar2);
        if (((cVar1 != '\0') &&
            (local_c = (**(code **)(*(int *)(local_8 + 0x18) + 0x30))(),
            (*(uint *)(local_c + 0x14) & 0x200) == 0)) &&
           ((iVar3 = FUN_00417e20(local_c), iVar3 != 0 ||
            (iVar3 = FUN_00462340(local_c), iVar3 != 0)))) {
          (**(code **)(*(int *)(local_8 + 0x18) + 0xc))();
          fVar4 = (float10)FUN_00462010();
          local_10 = (float)fVar4;
          if (local_10 < local_14) {
            local_18 = local_8;
            local_14 = local_10;
          }
        }
      }
    }
  }
  FUN_00477590(local_18);
  return;
}

