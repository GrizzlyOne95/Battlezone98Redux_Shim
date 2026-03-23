
void FUN_0047c210(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (**(code **)(*(int *)(param_1 + 0x18) + 4))();
  iVar2 = FUN_00461430();
  if (iVar1 == iVar2) {
    iVar1 = FUN_0045bba0();
    iVar2 = (*(code *)**(undefined4 **)(param_1 + 0x18))();
    if (*(int *)(iVar2 + 0x14) == 0x53434156) {
      FUN_0047c540(3);
    }
    else if ((iVar1 < 0xf) || (0x18 < iVar1)) {
      if ((iVar1 < 5) || (0xe < iVar1)) {
        FUN_0047c540(0);
      }
      else {
        FUN_0047c540(2);
      }
    }
    else {
      FUN_0047c540(1);
    }
  }
  return;
}

