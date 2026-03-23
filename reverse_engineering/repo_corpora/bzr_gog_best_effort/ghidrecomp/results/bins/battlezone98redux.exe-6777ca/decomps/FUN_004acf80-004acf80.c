
void __thiscall FUN_004acf80(int param_1,float param_2)

{
  if (param_2 < 0.5) {
    if (param_2 < 0.3) {
      if (param_2 < 0.2) {
        if (param_2 < 0.1) {
          *(undefined4 *)(param_1 + 0x238) = *(undefined4 *)(*(int *)(param_1 + 0xf8) + 0x324);
        }
        else {
          *(undefined4 *)(param_1 + 0x238) = *(undefined4 *)(*(int *)(param_1 + 0xf8) + 800);
        }
      }
      else {
        *(undefined4 *)(param_1 + 0x238) = *(undefined4 *)(*(int *)(param_1 + 0xf8) + 0x31c);
      }
    }
    else {
      *(undefined4 *)(param_1 + 0x238) = *(undefined4 *)(*(int *)(param_1 + 0xf8) + 0x318);
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x238) = 0;
  }
  return;
}

