
undefined2 * FUN_00780fd0(undefined2 *param_1,int param_2)

{
  *param_1 = *(undefined2 *)(&DAT_02cd9140 + param_2 * 3);
  *(undefined *)(param_1 + 1) = (&DAT_02cd9142)[param_2 * 3];
  return param_1;
}

