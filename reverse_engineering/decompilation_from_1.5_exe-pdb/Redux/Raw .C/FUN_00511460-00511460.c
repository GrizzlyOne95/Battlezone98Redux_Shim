
void __thiscall FUN_00511460(int param_1,float param_2)

{
  char cVar1;
  
  if (*(float *)(param_1 + 0x238) <= param_2 && param_2 != *(float *)(param_1 + 0x238)) {
    param_2 = *(float *)(param_1 + 0x238);
  }
  *(float *)(param_1 + 0x238) = *(float *)(param_1 + 0x238) - param_2;
  if (*(float *)(param_1 + 0x238) <= 0.0) {
    cVar1 = FUN_00571c40();
    if ((cVar1 != '\0') && ((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x80) == 0)) {
      *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) =
           *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) | 0x280;
      FUN_004b8460();
    }
    *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) = *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) | 0x280;
  }
  if ((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x200) != 0) {
    (**(code **)(*(int *)(param_1 + 0x18) + 0x14))();
  }
  return;
}

