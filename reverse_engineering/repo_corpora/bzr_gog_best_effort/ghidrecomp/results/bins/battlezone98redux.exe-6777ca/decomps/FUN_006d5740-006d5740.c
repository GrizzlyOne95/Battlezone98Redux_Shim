
void __thiscall FUN_006d5740(int param_1,int param_2)

{
  param_2 = *(int *)(param_1 + 4) - param_2;
  FID_conflict__Destroy(param_2,*(undefined4 *)(param_1 + 4));
  *(int *)(param_1 + 4) = param_2;
  return;
}

