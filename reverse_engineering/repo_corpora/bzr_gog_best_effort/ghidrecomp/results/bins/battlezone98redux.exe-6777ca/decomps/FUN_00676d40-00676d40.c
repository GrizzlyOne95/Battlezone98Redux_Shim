
void __thiscall FUN_00676d40(int param_1,int param_2)

{
  if (param_1 != param_2) {
    _Swap_adl<>(param_1,param_2);
    iter_swap<>(param_1 + 4,param_2 + 4);
  }
  return;
}

