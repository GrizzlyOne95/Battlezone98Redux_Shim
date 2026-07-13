
undefined4 __thiscall FUN_00476f90(int param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  float10 extraout_ST0;
  
  cVar1 = (**(code **)(**(int **)(param_1 + 0x34) + 0x68))();
  if (cVar1 == '\0') {
    uVar2 = 0;
  }
  else if (param_2 == 7) {
    uVar2 = 0;
  }
  else {
    uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 100) + 0x18) + 0xc))();
    uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x34) + 0x18) + 0xc))(uVar2);
    FUN_00462010(uVar2);
    if (*(float *)(param_1 + 0x68) <= (float)extraout_ST0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
  }
  return uVar2;
}

