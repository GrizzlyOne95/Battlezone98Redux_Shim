
void __thiscall FUN_004a77a0(int param_1,int param_2,int param_3)

{
  if ((-1 < param_2) && (param_2 < 5)) {
    *(int *)(param_1 + 0x18 + param_2 * 4) = param_3;
    if (param_3 == 0) {
      *(uint *)(param_1 + 0x2c) = ~(1 << ((byte)param_2 & 0x1f)) & *(uint *)(param_1 + 0x2c);
    }
    else {
      *(uint *)(param_1 + 0x2c) = 1 << ((byte)param_2 & 0x1f) | *(uint *)(param_1 + 0x2c);
    }
  }
  return;
}

