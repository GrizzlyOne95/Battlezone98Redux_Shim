
void __thiscall FUN_004236f0(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 4) + param_2 * -4;
  FID_conflict__Destroy(iVar1,*(undefined4 *)(param_1 + 4));
  *(int *)(param_1 + 4) = iVar1;
  return;
}

