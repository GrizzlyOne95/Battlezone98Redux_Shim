
void __thiscall FUN_005f2130(int param_1,int param_2)

{
  for (; param_2 != 0; param_2 = *(int *)(param_2 + 0x7c)) {
    if (*(int *)(param_2 + 0x84) == 0x41) {
      switch(*(undefined1 *)(param_2 + 0xe)) {
      case 0x58:
      case 0x78:
        *(int *)(param_1 + 0x310 + *(int *)(param_1 + 800) * 4) = param_2;
        *(int *)(param_1 + 800) = *(int *)(param_1 + 800) + 1;
        break;
      case 0x59:
      case 0x79:
        *(int *)(param_1 + 0x30c) = param_2;
        break;
      default:
        FUN_007d6a70("Invalid turret id \"%.8s\" in object \"%.8s\"",param_2 + 8,
                     *(int *)(param_1 + 0xf4) + 8);
      }
    }
    if (*(int *)(param_2 + 0x80) != 0) {
      FUN_005f2130(*(undefined4 *)(param_2 + 0x80));
    }
  }
  return;
}

