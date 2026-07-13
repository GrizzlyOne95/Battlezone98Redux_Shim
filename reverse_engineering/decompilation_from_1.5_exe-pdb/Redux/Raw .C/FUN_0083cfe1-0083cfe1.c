
void FUN_0083cfe1(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  while (param_2 != -1) {
    iVar1 = FUN_0083c3e8(param_1,param_2);
    iVar2 = FUN_0083d02b(param_1,param_2,param_4);
    uVar3 = param_5;
    if (iVar2 != 0) {
      uVar3 = param_3;
    }
    FUN_0083c362(param_1,param_2,uVar3);
    param_2 = iVar1;
  }
  return;
}

