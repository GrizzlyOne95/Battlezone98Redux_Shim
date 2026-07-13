
void __fastcall FUN_004fa1a0(int param_1)

{
  int local_10;
  undefined4 local_c;
  int local_8;
  
  if ((((*(int *)(param_1 + 0x18) != 0) && (*(char *)(*(int *)(param_1 + 0x18) + 0xb8) != '\0')) &&
      (*(int *)(param_1 + 0x1c) != 0)) && (*(char *)(*(int *)(param_1 + 0x1c) + 0xb8) != '\0')) {
    local_10 = 1;
    local_c = 1;
    local_8 = param_1;
    (**(code **)(**(int **)(*(int *)(param_1 + 0x18) + 0xb4) + 0xc))(&local_10);
    (**(code **)(**(int **)(*(int *)(local_8 + 0x1c) + 0xb4) + 0xc))(&local_c);
    *(undefined4 *)(local_8 + 0x20) = local_c;
    *(float *)(local_8 + 0x24) =
         1.0 / (float)((double)local_10 + (double)(&DAT_008a2fd0)[-(local_10 >> 0x1f)]);
    *(undefined4 *)(local_8 + 0x18) = 0;
    *(undefined4 *)(local_8 + 0x1c) = 0;
  }
  return;
}

