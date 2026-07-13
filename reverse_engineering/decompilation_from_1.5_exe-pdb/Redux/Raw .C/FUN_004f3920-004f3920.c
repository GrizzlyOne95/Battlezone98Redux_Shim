
void __fastcall FUN_004f3920(int param_1)

{
  undefined4 *puVar1;
  float10 fVar2;
  int local_c;
  
  for (local_c = 0; local_c < *(int *)(param_1 + 8); local_c = local_c + 1) {
    puVar1 = (undefined4 *)(param_1 + 0xc + local_c * 0x18);
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[2] = 0;
    puVar1[3] = 0;
    if (puVar1[4] != 0) {
      free((void *)puVar1[4]);
      puVar1[4] = 0;
    }
    puVar1[5] = 0;
  }
  *(undefined4 *)(param_1 + 8) = 0;
  fVar2 = (float10)FUN_00822da0();
  *(float *)(param_1 + 0xfc) = (float)fVar2;
  return;
}

