
void __thiscall FUN_0047c3e0(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  
  iVar1 = (**(code **)(*(int *)(param_2 + 0x18) + 4))();
  iVar2 = FUN_00461430();
  if ((iVar1 == iVar2) &&
     (fVar3 = (float10)FUN_00822d80(), *(float *)(param_1 + 0x210) <= (float)fVar3)) {
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x210) = (float)fVar3 + 30.0;
    iVar1 = FUN_0045bba0();
    iVar2 = (*(code *)**(undefined4 **)(param_2 + 0x18))();
    if ((*(int *)(iVar2 + 0x1c) == 6) || (*(int *)(iVar2 + 0x1c) == 1)) {
      if (iVar1 == 1) {
        FUN_0047c540(5);
      }
      else if (iVar1 == 2) {
        FUN_0047c540(5);
      }
      else if (iVar1 == 3) {
        FUN_0047c540(5);
      }
      else if ((0x4f < iVar1) && (iVar1 < 0x5a)) {
        FUN_0047c540(5);
      }
    }
    else if (*(int *)(iVar2 + 0x1c) == 2) {
      FUN_0047c540(5);
    }
  }
  return;
}

