
void FUN_0047c380(int param_1)

{
  int iVar1;
  float10 fVar2;
  
  if (param_1 != 0) {
    iVar1 = FUN_00417c70();
    if (param_1 == iVar1) {
      fVar2 = (float10)(**(code **)(*(int *)(param_1 + 0x18) + 0x1c))();
      if ((float)fVar2 < 0.25) {
        FUN_0047c540(8);
      }
    }
    else {
      FUN_0047c540(7);
    }
  }
  return;
}

