
void __thiscall FUN_004d2780(int param_1,float param_2)

{
  FUN_00480470(param_2);
  if (0 < *(int *)(*(int *)(param_1 + 0xc) + 0x80)) {
    *(float *)(param_1 + 0xec) = *(float *)(param_1 + 0xec) + param_2;
    while ((*(int *)(param_1 + 0xe8) < *(int *)(*(int *)(param_1 + 0xc) + 0x84) &&
           (*(float *)(*(int *)(param_1 + 0xc) + 0x7c) <= *(float *)(param_1 + 0xec)))) {
      *(int *)(param_1 + 0xe8) = *(int *)(param_1 + 0xe8) + 1;
      *(float *)(param_1 + 0xec) =
           *(float *)(param_1 + 0xec) - *(float *)(*(int *)(param_1 + 0xc) + 0x7c);
    }
  }
  return;
}

