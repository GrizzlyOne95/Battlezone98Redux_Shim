
void __thiscall FUN_0059d140(int param_1,float param_2)

{
  float10 fVar1;
  
  if (param_2 <= 0.0) {
    fVar1 = (float10)FUN_00447ed0(param_2 / *(float *)(*(int *)(param_1 + 0xf8) + 0x374),0xbf800000,
                                  0x3f800000);
    *(float *)(*(int *)(param_1 + 0x230) + 0xd0) = (float)fVar1;
  }
  else {
    fVar1 = (float10)FUN_00447ed0(param_2 / *(float *)(*(int *)(param_1 + 0xf8) + 0x370),0xbf800000,
                                  0x3f800000);
    *(float *)(*(int *)(param_1 + 0x230) + 0xd0) = (float)fVar1;
  }
  return;
}

