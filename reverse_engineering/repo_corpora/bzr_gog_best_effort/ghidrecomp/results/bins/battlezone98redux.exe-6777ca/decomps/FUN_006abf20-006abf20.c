
void FUN_006abf20(int *param_1,undefined1 *param_2,uint param_3)

{
  if (((param_3 < 0x100) && (param_1 != (int *)0x0)) && (*param_1 == 0)) {
    *param_2 = param_2[param_3];
    *param_1 = (int)param_2;
  }
  else {
    operator_delete(param_2);
  }
  return;
}

