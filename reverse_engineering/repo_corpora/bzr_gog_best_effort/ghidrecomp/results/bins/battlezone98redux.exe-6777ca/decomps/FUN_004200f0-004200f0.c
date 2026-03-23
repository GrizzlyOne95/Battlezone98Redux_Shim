
undefined4 __thiscall FUN_004200f0(int param_1,undefined4 param_2,int param_3)

{
  _Move<>(param_3 + 4,*(undefined4 *)(param_1 + 4),param_3);
  FID_conflict__Destroy(*(int *)(param_1 + 4) + -4,*(undefined4 *)(param_1 + 4));
  *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + -4;
  FID_conflict__Make_iter(param_2,param_3);
  return param_2;
}

