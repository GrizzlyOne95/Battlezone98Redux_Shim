
void __thiscall FUN_0047a3d0(int param_1,undefined4 param_2,undefined4 param_3)

{
  float10 fVar1;
  
  FUN_00480340(param_2,param_3);
  *(undefined8 *)(param_1 + 0xe8) = *(undefined8 *)(*(int *)(param_1 + 0x14) + 0x48);
  *(undefined8 *)(param_1 + 0xf0) = *(undefined8 *)(*(int *)(param_1 + 0x14) + 0x50);
  *(undefined8 *)(param_1 + 0xf8) = *(undefined8 *)(*(int *)(param_1 + 0x14) + 0x58);
  fVar1 = (float10)FUN_00822d60();
  *(float *)(param_1 + 200) = -(float)fVar1;
  return;
}

