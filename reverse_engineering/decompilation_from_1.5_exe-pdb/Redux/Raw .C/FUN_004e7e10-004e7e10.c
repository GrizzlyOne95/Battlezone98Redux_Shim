
void __thiscall FUN_004e7e10(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  float10 fVar2;
  double dVar3;
  undefined4 local_34;
  
  iVar1 = *(int *)(param_1 + 0x14);
  fVar2 = (float10)FUN_007855e0(*(undefined8 *)(iVar1 + 0x48),*(undefined8 *)(iVar1 + 0x58));
  dVar3 = (double)((float)fVar2 + 0.5);
  if (*(double *)(iVar1 + 0x50) <= dVar3 && dVar3 != *(double *)(iVar1 + 0x50)) {
    *(double *)(iVar1 + 0x50) = (double)(float)fVar2;
    for (local_34 = 0; local_34 < 0x14; local_34 = local_34 + 1) {
      FUN_004927d0();
    }
    FUN_007809d0();
  }
  FUN_00480750(param_2,param_3);
  FUN_0083e885();
  return;
}

