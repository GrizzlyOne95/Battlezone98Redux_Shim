
bool __fastcall FUN_005ff8a0(int *param_1)

{
  char cVar1;
  int iVar2;
  float10 fVar3;
  
  iVar2 = FUN_004cf880();
  param_1[5] = iVar2;
  iVar2 = FUN_004cf880();
  param_1[9] = iVar2;
  iVar2 = FUN_004cf880();
  param_1[0x1e] = iVar2;
  if ((float)param_1[0x21] == 0.0) {
    fVar3 = (float10)FUN_00822d80();
    param_1[0x21] = (int)(float)fVar3;
  }
  cVar1 = FUN_00435a30();
  if (param_1[0x41] != 0) {
    iVar2 = FUN_004775b0();
    param_1[0x41] = iVar2;
    FUN_004776e0(param_1[4],param_1);
    param_1[6] = 0;
  }
  if (param_1[0x47] != 0) {
    iVar2 = FUN_004d3130();
    param_1[0x47] = iVar2;
    FUN_004d3260();
    param_1[6] = 0;
  }
  param_1[0x12] = param_1[0x11];
  if (param_1[0x10] != 0) {
    param_1[0xd] = *(int *)(*(int *)(param_1[0x10] + 8) + -8 + *(int *)(param_1[0x10] + 4) * 8);
    param_1[0xf] = *(int *)(*(int *)(param_1[0x10] + 8) + -4 + *(int *)(param_1[0x10] + 4) * 8);
    fVar3 = (float10)FUN_007855e0((double)(float)param_1[0xd],(double)(float)param_1[0xf]);
    param_1[0xe] = (int)(float)fVar3;
  }
  (**(code **)(*param_1 + 0x14))();
  return cVar1 != '\0';
}

