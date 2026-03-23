
void __fastcall FUN_005f5970(int param_1)

{
  float fVar1;
  float10 fVar2;
  
  if (*(int *)(param_1 + 0x36c) != 0) {
    fVar2 = (float10)FUN_00462470();
    fVar1 = (float)fVar2;
    FUN_00469840(*(float *)(param_1 + 0x370) - fVar1,*(float *)(param_1 + 0x374) - fVar1,
                 *(float *)(param_1 + 0x370) + fVar1,*(float *)(param_1 + 0x374) + fVar1,0);
    FUN_00469900(*(undefined4 *)(param_1 + 0x370),*(undefined4 *)(param_1 + 0x374),0x43160000,
                 *(undefined4 *)(param_1 + 0x36c),0);
    *(undefined4 *)(param_1 + 0x36c) = 0;
  }
  return;
}

