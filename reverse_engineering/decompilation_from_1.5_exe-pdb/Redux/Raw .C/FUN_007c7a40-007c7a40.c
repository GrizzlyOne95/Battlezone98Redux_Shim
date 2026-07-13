
uint FUN_007c7a40(int param_1)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  
  uVar1 = size();
  if (uVar1 < 2) {
    uVar1 = uVar1 & 0xffffff00;
  }
  else {
    iVar2 = size();
    piVar3 = (int *)FUN_004200d0(iVar2 + -1);
    uVar1 = CONCAT31((int3)((uint)*piVar3 >> 8),*piVar3 == param_1);
  }
  return uVar1;
}

