
void __thiscall FUN_0049f3c0(int *param_1,char param_2)

{
  if ((param_2 == '\0') || (*(char *)((int)param_1 + 0x18a) != '\0')) {
    if ((param_2 == '\0') && (*(char *)((int)param_1 + 0x18a) != '\0')) {
      (**(code **)(*param_1 + 0x24))();
    }
  }
  else {
    (**(code **)(*param_1 + 0x20))();
  }
  *(char *)((int)param_1 + 0x18a) = param_2;
  return;
}

