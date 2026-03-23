
void FUN_007cf2b0(int param_1,int param_2)

{
  for (; (param_1 != param_2 && (param_2 = param_2 + -0x18, param_1 != param_2));
      param_1 = param_1 + 0x18) {
    iter_swap<>(param_1,param_2);
  }
  return;
}

