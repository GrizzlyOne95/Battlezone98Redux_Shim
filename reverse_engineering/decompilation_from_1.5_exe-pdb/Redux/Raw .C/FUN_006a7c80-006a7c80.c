
void __fastcall FUN_006a7c80(int param_1)

{
  int iVar1;
  undefined8 local_24;
  undefined8 local_1c;
  undefined4 local_14;
  undefined4 local_10;
  
  local_24 = 1000000000.0;
  local_1c = -1000000000.0;
  for (local_10 = 0; local_10 < *(int *)(*(int *)(param_1 + 0x44) + 0x80); local_10 = local_10 + 1)
  {
    for (local_14 = 0; local_14 < *(int *)(*(int *)(param_1 + 0x44) + 0x84); local_14 = local_14 + 1
        ) {
      iVar1 = *(int *)(*(int *)(*(int *)(*(int *)(param_1 + 0x40) + 0x80) + local_10 * 4) +
                      local_14 * 4);
      *(undefined4 *)(iVar1 + 0x24) = *(undefined4 *)(iVar1 + 0x20);
      if (-5e+08 < *(float *)(iVar1 + 0x24)) {
        if ((double)*(float *)(iVar1 + 0x24) < local_24) {
          local_24 = (double)*(float *)(iVar1 + 0x24);
        }
        if (local_1c < (double)*(float *)(iVar1 + 0x24)) {
          local_1c = (double)*(float *)(iVar1 + 0x24);
        }
      }
    }
  }
  *(double *)(param_1 + 0x88) = local_1c;
  *(double *)(param_1 + 0x90) = local_24;
  return;
}

