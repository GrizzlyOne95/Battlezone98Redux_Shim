
int FUN_00838869(int param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0x10);
  iVar2 = (**(code **)(iVar1 + 0xc))(*(undefined4 *)(iVar1 + 0x10),param_2,param_3,param_4);
  if ((iVar2 == 0) && (param_4 != 0)) {
    FUN_0082f657(param_1,4);
  }
  *(int *)(iVar1 + 0x44) = *(int *)(iVar1 + 0x44) + (param_4 - param_3);
  return iVar2;
}

