
void __thiscall FUN_007ccd50(int param_1,undefined4 param_2,undefined4 param_3)

{
  _snprintf((char *)(param_1 + 0x144),0x2800,"%%%d%s",param_3,param_2);
  switch(param_3) {
  case 0:
    *(uint *)(param_1 + 0x100) = *(uint *)(param_1 + 0x100) & 0xff000000 | 0xffffff;
    break;
  case 1:
    *(uint *)(param_1 + 0x100) = *(uint *)(param_1 + 0x100) & 0xff000000;
    break;
  case 2:
    *(uint *)(param_1 + 0x100) = *(uint *)(param_1 + 0x100) & 0xff000000 | 0xff0000;
    break;
  default:
    *(uint *)(param_1 + 0x100) = *(uint *)(param_1 + 0x100) & 0xff000000 | 0xff00;
    break;
  case 4:
    *(uint *)(param_1 + 0x100) = *(uint *)(param_1 + 0x100) & 0xff000000 | 0x3333ff;
  }
  FUN_007ccfc0();
  return;
}

