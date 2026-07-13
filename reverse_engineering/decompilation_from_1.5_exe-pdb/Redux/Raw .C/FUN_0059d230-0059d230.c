
void __thiscall FUN_0059d230(int param_1,undefined4 param_2,undefined4 param_3)

{
  float fVar1;
  float10 fVar2;
  undefined8 uVar3;
  
  uVar3 = FUN_004622a0(param_2,param_3);
  fVar1 = (float)((ulonglong)uVar3 >> 0x20);
  fVar2 = (float10)FUN_00447ed0(((float)uVar3 * *(float *)(*(int *)(param_1 + 0xf4) + 0x20) +
                                fVar1 * *(float *)(*(int *)(param_1 + 0xf4) + 0x28)) * -5.0,
                                0xbf800000,0x3f800000);
  *(float *)(*(int *)(param_1 + 0x230) + 0xc4) = (float)fVar2;
  fVar2 = (float10)FUN_00447ed0(((float)uVar3 * *(float *)(*(int *)(param_1 + 0xf4) + 0x38) +
                                fVar1 * *(float *)(*(int *)(param_1 + 0xf4) + 0x40)) * 5.0,
                                0xbf800000,0x3f800000);
  *(float *)(*(int *)(param_1 + 0x230) + 0xd0) = (float)fVar2;
  return;
}

