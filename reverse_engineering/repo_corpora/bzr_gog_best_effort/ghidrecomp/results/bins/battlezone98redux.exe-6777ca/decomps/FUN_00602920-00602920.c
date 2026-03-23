
void __fastcall FUN_00602920(int param_1)

{
  undefined4 *puVar1;
  float10 fVar2;
  
  fVar2 = (float10)FUN_00822d80();
  *(float *)(param_1 + 0x84) = (float)fVar2 + 5.0;
  puVar1 = (undefined4 *)(**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))();
  *(undefined4 *)(param_1 + 0x88) = *puVar1;
  *(undefined4 *)(param_1 + 0x8c) = puVar1[1];
  *(undefined4 *)(param_1 + 0x90) = puVar1[2];
  *(uint *)(*(int *)(*(int *)(param_1 + 0x10) + 0x230) + 0x114) =
       *(uint *)(*(int *)(*(int *)(param_1 + 0x10) + 0x230) + 0x114) & 0xfffdffff;
  return;
}

