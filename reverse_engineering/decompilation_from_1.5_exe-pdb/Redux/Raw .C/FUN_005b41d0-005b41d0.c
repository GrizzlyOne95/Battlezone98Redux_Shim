
void __fastcall FUN_005b41d0(int *param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  float10 fVar6;
  float10 fVar7;
  undefined1 local_14;
  
  cVar1 = (**(code **)(*(int *)param_1[8] + 0x68))();
  if ((cVar1 == '\0') && (cVar1 = (**(code **)(*(int *)param_1[8] + 0x6c))(), cVar1 == '\0')) {
    local_14 = 1;
  }
  else {
    local_14 = 0;
  }
  *(undefined1 *)(param_1 + 0xe) = local_14;
  if ((*(char *)((int)param_1 + 0x39) != '\0') && ((char)param_1[0xe] == '\0')) {
    cVar1 = (**(code **)(*(int *)param_1[8] + 0x68))();
    if (cVar1 == '\0') {
      FUN_005f91e0(param_1[8],0x17,0);
    }
    else {
      FUN_005f91e0(param_1[8],0x16,0);
    }
  }
  switch(param_1[6]) {
  case 1:
  case 2:
  case 3:
    (**(code **)(*param_1 + 0x2c))();
    break;
  case 4:
  case 5:
  case 8:
    cVar1 = (**(code **)(*(int *)param_1[0xb] + 0x18))();
    if (cVar1 == '\0') {
      (**(code **)(*(int *)param_1[0xb] + 0x1c))();
    }
    else {
      param_1[7] = 3;
    }
    break;
  case 6:
    cVar1 = FUN_004723d0();
    if (cVar1 == '\0') {
      FUN_005f91e0(param_1[8],0x11,0);
      param_1[7] = 2;
    }
    else {
      (**(code **)(*param_1 + 0x2c))();
    }
    break;
  case 7:
    if ((param_1[0xb] == 0) || (cVar1 = (**(code **)(*(int *)param_1[0xb] + 0x18))(), cVar1 != '\0')
       ) {
      iVar2 = FUN_00473940();
      if (iVar2 != 0) {
        iVar3 = FUN_00462400();
        fVar6 = (float10)FUN_00462470(*(undefined4 *)(iVar3 + 0xc));
        fVar6 = (float10)FUN_0044fb20((float)fVar6);
        iVar3 = FUN_00462400();
        fVar7 = (float10)FUN_00462470(*(undefined4 *)(iVar3 + 0xc));
        fVar7 = (float10)FUN_0044fb20((float)fVar7);
        fVar6 = (float10)FUN_0044fb20((float)fVar6 + (float)fVar7 + 10.0,0x42200000);
        pfVar4 = (float *)(**(code **)(*(int *)(iVar2 + 0x18) + 0xc))();
        pfVar5 = (float *)(**(code **)(*(int *)(param_1[8] + 0x18) + 0xc))();
        fVar7 = (float10)FUN_00453f80(*pfVar4 - *pfVar5);
        if ((float)fVar7 < (float)fVar6) {
          iVar2 = (**(code **)(*(int *)(iVar2 + 0x18) + 0xc))();
          iVar3 = (**(code **)(*(int *)(param_1[8] + 0x18) + 0xc))();
          fVar7 = (float10)FUN_00453f80(*(float *)(iVar2 + 8) - *(float *)(iVar3 + 8));
          if ((float)fVar7 < (float)fVar6) {
            (**(code **)(*(int *)(param_1[8] + 0x18) + 0x24))();
          }
        }
      }
      if (*(int *)(param_1[8] + 0xac) == 0x12) {
        FUN_004dbc00();
      }
      param_1[7] = 3;
      return;
    }
    (**(code **)(*(int *)param_1[0xb] + 0x1c))();
  }
  *(char *)((int)param_1 + 0x39) = (char)param_1[0xe];
  return;
}

