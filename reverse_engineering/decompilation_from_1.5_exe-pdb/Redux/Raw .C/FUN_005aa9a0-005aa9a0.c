
void __thiscall FUN_005aa9a0(undefined4 param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  
  iVar1 = FUN_004b9ab0(*param_2,param_1);
  if (iVar1 != 0) {
    FUN_0046fc40(iVar1);
  }
  iVar1 = FUN_004b9ab0(param_2[1],param_1);
  if (iVar1 != 0) {
    FUN_0049f450(iVar1);
  }
  FUN_004dff70(param_2 + 2,param_3 + -8);
  return;
}

