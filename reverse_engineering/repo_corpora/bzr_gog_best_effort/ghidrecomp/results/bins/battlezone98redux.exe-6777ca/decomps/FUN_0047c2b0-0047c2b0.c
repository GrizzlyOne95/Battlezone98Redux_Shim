
void FUN_0047c2b0(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (**(code **)(*(int *)(param_1 + 0x18) + 4))();
  iVar2 = FUN_00461430();
  if (iVar1 == iVar2) {
    iVar1 = FUN_0045bba0();
    iVar2 = (*(code *)**(undefined4 **)(param_1 + 0x18))();
    if (*(int *)(iVar2 + 0x1c) == 2) {
      if ((iVar1 < 0x2d) || (0x36 < iVar1)) {
        FUN_0047c540(0xd);
      }
      else {
        FUN_0047c540(0xb);
      }
    }
  }
  return;
}

