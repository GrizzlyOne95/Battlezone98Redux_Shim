
void __thiscall FUN_007cca20(int param_1,undefined4 param_2)

{
  switch(param_2) {
  case 0:
    *(uint *)(param_1 + 0x91c) = *(uint *)(param_1 + 0x91c) & 0xff000000 | 0xffffff;
    break;
  case 1:
    *(uint *)(param_1 + 0x91c) = *(uint *)(param_1 + 0x91c) & 0xff000000;
    break;
  case 2:
    *(uint *)(param_1 + 0x91c) = *(uint *)(param_1 + 0x91c) & 0xff000000 | 0xff0000;
    break;
  default:
    *(uint *)(param_1 + 0x91c) = *(uint *)(param_1 + 0x91c) & 0xff000000 | 0xff00;
    break;
  case 4:
    *(uint *)(param_1 + 0x91c) = *(uint *)(param_1 + 0x91c) & 0xff000000 | 0x3333ff;
  }
  FUN_007cc750();
  return;
}

