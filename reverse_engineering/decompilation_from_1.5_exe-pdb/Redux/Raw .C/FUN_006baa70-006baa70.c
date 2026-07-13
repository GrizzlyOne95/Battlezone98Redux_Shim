
void __thiscall FUN_006baa70(void *param_1,void *param_2)

{
  if (param_2 == param_1) {
    *(undefined1 *)((int)param_1 + 0x400) = 0;
  }
  else {
    operator_delete(param_2);
  }
  return;
}

