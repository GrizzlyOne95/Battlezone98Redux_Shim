
void __thiscall
FUN_004b7e60(int *param_1,undefined2 param_2,undefined4 param_3,int param_4,int param_5)

{
  if (*(short *)((int)param_1 + 0x62) == 0) {
    *(undefined2 *)((int)param_1 + 0x62) = param_2;
  }
  if ((*(byte *)(param_4 + 0x14) & 0x80) == 0) {
    if ((*(byte *)(param_4 + 1) & 3) == 0) {
      (**(code **)(*param_1 + 0x48))(param_4 + 0x1c,param_5 + -0x1c);
    }
  }
  else if ((*(byte *)(param_4 + 1) & 3) == 0) {
    (**(code **)(*param_1 + 0x48))(param_4 + 0x15,param_5 + -0x15);
  }
  return;
}

