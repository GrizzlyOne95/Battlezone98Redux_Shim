
int __thiscall
FUN_004ff320(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0082d465(param_2,param_3,param_1);
  if ((iVar1 != 0) && (iVar2 = FUN_0082c882(param_2,param_3), iVar2 != 0)) {
    FUN_0082c82c(param_2,0xffffd8f0,param_4);
    iVar2 = FUN_0082ce29(param_2,0xffffffff,0xfffffffe);
    if (iVar2 == 0) {
      iVar1 = 0;
    }
    FUN_0082d226(param_2,0xfffffffd);
    return iVar1;
  }
  return 0;
}

