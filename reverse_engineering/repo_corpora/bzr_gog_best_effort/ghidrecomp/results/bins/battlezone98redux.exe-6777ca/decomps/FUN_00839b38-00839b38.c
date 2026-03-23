
void FUN_00839b38(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0083b6c3(param_1,param_2);
  if (iVar1 == 0) {
    if (param_4 == *(int *)(param_1 + 4)) {
      FUN_0083a05e(param_1,param_2);
    }
    else {
      uVar2 = FUN_008390ce(param_1,param_3,param_4);
      uVar2 = FUN_008390ce(param_1,param_2,uVar2);
      uVar2 = FUN_0082e8cd(*(undefined4 *)(param_1 + 0x34),
                           "\'%s\' expected (to close \'%s\' at line %d)",uVar2);
      FUN_008390b7(param_1,uVar2);
    }
  }
  return;
}

