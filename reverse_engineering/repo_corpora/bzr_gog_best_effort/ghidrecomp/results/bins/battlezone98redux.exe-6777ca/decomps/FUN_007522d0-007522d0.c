
void __thiscall
FUN_007522d0(int param_1,undefined4 param_2,undefined1 param_3,int param_4,int param_5)

{
  if ((param_4 == *(int *)(param_1 + 0x10)) && (param_5 == *(int *)(param_1 + 0x14))) {
    *(undefined4 *)(param_1 + 0x10) = 0;
    *(undefined4 *)(param_1 + 0x14) = 0;
    (**(code **)(param_1 + 0x1c))(param_2,param_3);
  }
  return;
}

