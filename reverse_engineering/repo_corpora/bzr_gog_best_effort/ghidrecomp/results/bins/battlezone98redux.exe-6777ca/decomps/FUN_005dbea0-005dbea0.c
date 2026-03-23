
void __thiscall FUN_005dbea0(int param_1,float param_2)

{
  int *piVar1;
  float10 fVar2;
  
  piVar1 = (int *)FUN_00417c70();
  if (piVar1 != (int *)0x0) {
    fVar2 = (float10)(**(code **)(piVar1[6] + 0x1c))(param_2 * 2.0);
    fVar2 = (float10)FUN_004c1050(*(undefined4 *)(param_1 + 0x18),(float)fVar2);
    *(float *)(param_1 + 0x18) = (float)fVar2;
    fVar2 = (float10)(**(code **)(*piVar1 + 0x1c))(param_2 * 2.0);
    fVar2 = (float10)FUN_004c1050(*(undefined4 *)(param_1 + 0x24),(float)fVar2);
    *(float *)(param_1 + 0x24) = (float)fVar2;
  }
  return;
}

