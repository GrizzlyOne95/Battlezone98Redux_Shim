
undefined4 * __thiscall
FUN_0046f190(undefined4 *param_1,undefined4 param_2,int param_3,undefined1 param_4,
            undefined1 param_5,undefined4 param_6,undefined4 param_7)

{
  undefined4 *local_c;
  undefined4 *local_8;
  
  *param_1 = param_2;
  param_1[1] = param_3;
  *(undefined1 *)(param_1 + 2) = param_4;
  *(undefined1 *)((int)param_1 + 9) = param_5;
  param_1[3] = param_6;
  param_1[4] = param_7;
  local_c = param_1;
  local_8 = param_1;
  FUN_00438be0(&local_c);
  (&DAT_0260d6c4)[param_3] = 1;
  DAT_0260d111 = 1;
  *(undefined1 *)(local_8 + 5) = 0;
  return local_8;
}

