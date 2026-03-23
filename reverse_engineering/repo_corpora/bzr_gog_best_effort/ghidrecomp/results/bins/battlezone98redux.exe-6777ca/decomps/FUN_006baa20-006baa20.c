
void * __thiscall FUN_006baa20(void *param_1,uint param_2)

{
  if ((*(char *)((int)param_1 + 0x400) == '\0') && (param_2 < 0x400)) {
    *(undefined1 *)((int)param_1 + 0x400) = 1;
  }
  else {
    param_1 = operator_new(param_2);
  }
  return param_1;
}

