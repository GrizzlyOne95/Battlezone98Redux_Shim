
void FUN_007e4b40(undefined4 param_1,undefined4 *param_2,int param_3)

{
  if (param_3 == 4) {
    *param_2 = &.??@1701b513cb02cc8c4941a1b4e0b52557@::RTTI_Type_Descriptor;
    *(undefined1 *)(param_2 + 1) = 0;
    *(undefined1 *)((int)param_2 + 5) = 0;
  }
  else {
    _Find_unchecked<>(param_1,param_2,param_3,0);
  }
  return;
}

