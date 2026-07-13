
int FUN_0083600d(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0xc);
  if ((iVar1 == 0) && (param_2 != 0)) {
    iVar1 = 1;
  }
  FUN_0082bb89(*(undefined4 *)(param_1 + 8),iVar1,"too many captures");
  iVar2 = 0;
  if (0 < iVar1) {
    do {
      FUN_00836056(param_1,iVar2,param_2,param_3);
      iVar2 = iVar2 + 1;
    } while (iVar2 < iVar1);
  }
  return iVar1;
}

