
void __thiscall FUN_0046fa60(int param_1,int param_2,int param_3,char param_4)

{
  undefined4 local_c;
  
  if ((-1 < param_2) && (param_2 < 0xb)) {
    if ((*(int *)(param_1 + 0x30) == param_2) && (*(int *)(param_1 + param_2 * 4) != param_3)) {
      *(undefined4 *)(param_1 + 0x30) = 0xffffffff;
    }
    *(int *)(param_1 + param_2 * 4) = param_3;
    if (param_4 == '\0') {
      local_c = ~(1 << ((byte)param_2 & 0x1f)) & *(uint *)(param_1 + 0x2c);
    }
    else {
      local_c = 1 << ((byte)param_2 & 0x1f) | *(uint *)(param_1 + 0x2c);
    }
    *(uint *)(param_1 + 0x2c) = local_c;
  }
  return;
}

