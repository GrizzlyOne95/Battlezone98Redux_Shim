
void __thiscall FUN_005afa70(int param_1,char *param_2,int *param_3)

{
  FUN_005af7b0();
  if (*param_2 == '\0') {
    (**(code **)(*(int *)(param_1 + -0x18) + 100))();
  }
  else if (*param_2 == '\x01') {
    (**(code **)(*(int *)(param_1 + -0x18) + 0x60))();
  }
  else if (*param_2 == '\x02') {
    (**(code **)(*(int *)(param_1 + -0x18) + 0x60))();
  }
  else if (*param_2 == '\x03') {
    (**(code **)(*(int *)(param_1 + -0x18) + 100))();
  }
  *param_3 = *param_3 + -1;
  FUN_004ef240(param_2 + 1,param_3);
  return;
}

