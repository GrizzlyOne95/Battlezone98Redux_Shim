
undefined4 FUN_00445220(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(param_1 + 0x84);
  if ((iVar1 == 2) || ((7 < iVar1 && (iVar1 < 0xb)))) {
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

