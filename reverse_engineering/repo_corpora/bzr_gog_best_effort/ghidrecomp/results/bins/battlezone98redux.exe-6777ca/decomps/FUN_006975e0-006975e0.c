
float10 __thiscall FUN_006975e0(int *param_1,undefined4 param_2)

{
  int iVar1;
  float10 fVar2;
  float local_c;
  
  iVar1 = FUN_00417f90();
  if (iVar1 == 0) {
    fVar2 = (float10)(**(code **)(*param_1 + 0x10))(param_2);
    if (*(int *)(param_1[0xf] + 0x60) == 0) {
      local_c = (float)*(int *)(*(int *)(param_1[0xf] + 0x60) + 0xc) * (float)fVar2 +
                (float)param_1[0x14];
    }
    else {
      local_c = (float)*(int *)(*(int *)(param_1[0xf] + 0x60) + 0xc) * (float)fVar2 +
                (float)*(int *)(*(int *)(param_1[0xf] + 0x60) + 0x30);
    }
    if ((float)param_1[7] <= local_c && local_c != (float)param_1[7]) {
      param_1[7] = (int)local_c;
    }
    fVar2 = (float10)local_c;
  }
  else {
    fVar2 = (float10)0;
  }
  return fVar2;
}

