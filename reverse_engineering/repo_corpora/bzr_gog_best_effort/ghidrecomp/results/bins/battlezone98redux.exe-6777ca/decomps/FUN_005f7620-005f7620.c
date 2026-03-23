
void __fastcall FUN_005f7620(int param_1)

{
  int iVar1;
  float10 fVar2;
  
  iVar1 = FUN_004624b0();
  if (*(float *)(iVar1 + 4) <= 10.0) {
    (**(code **)(**(int **)(param_1 + 0x34) + 0x60))();
  }
  else {
    fVar2 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x84) = (float)fVar2 + 10.0;
  }
  FUN_005fb330();
  return;
}

