
void FUN_005cd820(float *param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  float10 fVar3;
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
  while (cVar1 = FUN_00462710(&local_20), cVar1 != '\0') {
    local_8 = FUN_00462630(*local_20);
    if ((((local_8 != 0) && (local_8 != param_2)) &&
        (iVar2 = (**(code **)(*(int *)(local_8 + 0x18) + 4))(), iVar2 == param_3)) &&
       (((iVar2 = FUN_004625b0(), iVar2 == param_3 &&
         (local_c = (**(code **)(*(int *)(local_8 + 0x18) + 0x30))(),
         (*(uint *)(local_c + 0x14) & 0x200) == 0)) &&
        ((iVar2 = FUN_00417e20(local_c), iVar2 != 0 || (iVar2 = FUN_00462340(local_c), iVar2 != 0)))
        ))) {
      (**(code **)(*(int *)(local_8 + 0x18) + 0xc))();
      fVar3 = (float10)FUN_00462010();
      local_10 = (float)fVar3;
      if (local_10 < local_14) {
        local_18 = local_8;
        local_14 = local_10;
      }
    }
  }
  FUN_00477590(local_18);
  return;
}

