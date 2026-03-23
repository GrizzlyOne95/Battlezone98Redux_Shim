
void __thiscall FUN_00829890(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 4) + param_2 * -0x1004;
  FID_conflict__Destroy(iVar1,*(undefined4 *)(param_1 + 4));
  *(int *)(param_1 + 4) = iVar1;
  return;
}

