
void FUN_0083b36f(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar1 = FUN_0083b57b(param_1);
  uVar3 = *(undefined4 *)(param_1 + 0x30);
  iVar2 = FUN_0083b3a9(uVar3,uVar1,param_2,1);
  if (iVar2 == 8) {
    uVar3 = FUN_0083cf81(uVar3,uVar1);
    *(undefined4 *)(param_2 + 8) = uVar3;
  }
  return;
}

