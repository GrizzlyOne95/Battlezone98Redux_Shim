
void __thiscall FUN_004c0410(int param_1,float param_2)

{
  undefined4 *puVar1;
  int iVar2;
  double *pdVar3;
  double *local_8;
  
  for (local_8 = (double *)(param_1 + 0x28); local_8 < *(double **)(param_1 + 0x18028);
      local_8 = local_8 + 6) {
    *(float *)((int)local_8 + 0x24) =
         param_2 * *(float *)(param_1 + 0x18034) + *(float *)((int)local_8 + 0x24);
    *(undefined4 *)(param_1 + 0x18030) = 0x10;
    if (*(float *)((int)local_8 + 0x24) <
        (float)(*(int *)(param_1 + 0x1802c) + *(int *)(param_1 + 0x18030))) {
      *(float *)(local_8 + 5) = param_2 * *(float *)(param_1 + 0x1803c) + *(float *)(local_8 + 5);
      *local_8 = (double)(*(float *)(local_8 + 3) * param_2) + *local_8;
      local_8[1] = (double)(*(float *)((int)local_8 + 0x1c) * param_2) + local_8[1];
      local_8[2] = (double)(*(float *)(local_8 + 4) * param_2) + local_8[2];
    }
    else {
      puVar1 = (undefined4 *)(*(int *)(param_1 + 0x18028) + -0x30);
      *(undefined4 **)(param_1 + 0x18028) = puVar1;
      pdVar3 = local_8;
      for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
        *(undefined4 *)pdVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        pdVar3 = (double *)((int)pdVar3 + 4);
      }
      local_8 = local_8 + -6;
    }
  }
  return;
}

