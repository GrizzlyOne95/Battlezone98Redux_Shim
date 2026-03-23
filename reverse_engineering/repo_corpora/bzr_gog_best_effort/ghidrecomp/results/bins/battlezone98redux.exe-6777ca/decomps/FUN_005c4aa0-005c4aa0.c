
void __fastcall FUN_005c4aa0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  float *pfVar6;
  float10 fVar7;
  float10 fVar8;
  
  switch(*(undefined4 *)(param_1 + 0x1c)) {
  case 1:
    fVar7 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0x44) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x44)) {
      *(undefined4 *)(param_1 + 0x20) = 4;
    }
    (**(code **)(**(int **)(param_1 + 0x58) + 0x1c))();
    break;
  case 2:
    cVar1 = (**(code **)(**(int **)(param_1 + 0x58) + 0x18))();
    if (cVar1 == '\0') {
      (**(code **)(**(int **)(param_1 + 0x58) + 0x1c))();
    }
    else {
      if (*(char *)(param_1 + 0x48) == '\0') {
        *(undefined4 *)(param_1 + 0x44) = 0x7149f2ca;
        *(undefined4 *)(param_1 + 0x20) = 1;
      }
      else {
        *(undefined4 *)(param_1 + 0x20) = 4;
      }
      *(undefined1 *)(param_1 + 0x48) = 0;
    }
    break;
  case 3:
    cVar1 = (**(code **)(**(int **)(param_1 + 0x58) + 0x18))();
    if (cVar1 == '\0') {
      (**(code **)(**(int **)(param_1 + 0x58) + 0x1c))();
    }
    else {
      *(undefined4 *)(param_1 + 0x20) = 1;
    }
    break;
  case 4:
    cVar1 = (**(code **)(**(int **)(param_1 + 0x58) + 0x18))();
    if (cVar1 != '\0') {
      *(undefined4 *)(param_1 + 0x20) = 1;
      return;
    }
    fVar7 = (float10)FUN_00822d80();
    if (*(float *)(param_1 + 0x44) <= (float)fVar7 && (float)fVar7 != *(float *)(param_1 + 0x44)) {
      fVar7 = (float10)FUN_00822d80();
      fVar8 = (float10)FUN_0046d040();
      if (5.0 <= (float)fVar7 - (float)fVar8) {
        fVar7 = (float10)FUN_00822d80();
        fVar8 = (float10)FUN_00497890();
        if (5.0 <= (float)fVar7 - (float)fVar8) goto LAB_005c4c25;
      }
      iVar3 = FUN_005c3140(*(undefined4 *)(param_1 + 0x28));
      if (iVar3 != 0) {
        uVar2 = (**(code **)(*(int *)(iVar3 + 0x18) + 0xc))();
        uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x28) + 0x18) + 0xc))(uVar2);
        fVar7 = (float10)FUN_00462010(uVar2);
        if (5625.0 < (float)fVar7) {
          *(undefined4 *)(param_1 + 0x20) = 7;
          return;
        }
      }
    }
LAB_005c4c25:
    (**(code **)(**(int **)(param_1 + 0x58) + 0x1c))();
    break;
  case 5:
    FUN_005c53b0();
    break;
  case 6:
    cVar1 = (**(code **)(**(int **)(param_1 + 0x58) + 0x18))();
    if (cVar1 == '\0') {
      (**(code **)(**(int **)(param_1 + 0x58) + 0x1c))();
    }
    else {
      *(undefined4 *)(param_1 + 0x20) = 1;
    }
    break;
  case 7:
    cVar1 = (**(code **)(**(int **)(param_1 + 0x58) + 0x18))();
    if (cVar1 == '\0') {
      uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x28) + 0x18) + 0xc))(param_1 + 0x2c);
      fVar7 = (float10)FUN_00462010(uVar2);
      if (1600.0 <= (float)fVar7) {
        (**(code **)(**(int **)(param_1 + 0x58) + 0x1c))();
      }
      else {
        *(undefined4 *)(param_1 + 0x20) = 1;
      }
    }
    else {
      *(undefined4 *)(param_1 + 0x20) = 1;
    }
    break;
  case 8:
    if ((*(int *)(param_1 + 0x58) == 0) ||
       (cVar1 = (**(code **)(**(int **)(param_1 + 0x58) + 0x18))(), cVar1 != '\0')) {
      iVar3 = FUN_00473940();
      if (iVar3 != 0) {
        iVar4 = FUN_00462400();
        fVar7 = (float10)FUN_00462470(*(undefined4 *)(iVar4 + 0xc));
        fVar7 = (float10)FUN_0044fb20((float)fVar7);
        iVar4 = FUN_00462400();
        fVar8 = (float10)FUN_00462470(*(undefined4 *)(iVar4 + 0xc));
        fVar8 = (float10)FUN_0044fb20((float)fVar8);
        fVar7 = (float10)FUN_0044fb20((float)fVar7 + (float)fVar8 + 10.0,0x42200000);
        pfVar5 = (float *)(**(code **)(*(int *)(iVar3 + 0x18) + 0xc))();
        pfVar6 = (float *)(**(code **)(*(int *)(*(int *)(param_1 + 0x28) + 0x18) + 0xc))();
        fVar8 = (float10)FUN_00453f80(*pfVar5 - *pfVar6);
        if ((float)fVar8 < (float)fVar7) {
          iVar3 = (**(code **)(*(int *)(iVar3 + 0x18) + 0xc))();
          iVar4 = (**(code **)(*(int *)(*(int *)(param_1 + 0x28) + 0x18) + 0xc))();
          fVar8 = (float10)FUN_00453f80(*(float *)(iVar3 + 8) - *(float *)(iVar4 + 8));
          if ((float)fVar8 < (float)fVar7) {
            (**(code **)(*(int *)(*(int *)(param_1 + 0x28) + 0x18) + 0x24))();
          }
        }
      }
      if (*(int *)(*(int *)(param_1 + 0x28) + 0xac) == 0x12) {
        FUN_004dbc00();
      }
      *(undefined4 *)(param_1 + 0x20) = 1;
    }
    else {
      (**(code **)(**(int **)(param_1 + 0x58) + 0x1c))();
    }
  }
  return;
}

