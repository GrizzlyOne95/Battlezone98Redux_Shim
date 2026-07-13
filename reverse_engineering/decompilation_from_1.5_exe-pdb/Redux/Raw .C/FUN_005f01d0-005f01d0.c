
void __thiscall FUN_005f01d0(int param_1,int param_2)

{
  do {
    if (param_2 == 0) {
      return;
    }
    if (*(int *)(param_2 + 0x84) == 0x41) {
      switch(*(undefined1 *)(param_2 + 0xe)) {
      case 0x58:
      case 0x78:
        *(int *)(param_1 + 0x2ac + *(int *)(param_1 + 700) * 4) = param_2;
        *(int *)(param_1 + 700) = *(int *)(param_1 + 700) + 1;
        break;
      default:
        FUN_007d6a70("Unusual turret id \"%.8s\" in object \"%.8s\"; assuming Y\n",param_2 + 8,
                     *(int *)(param_1 + 0xf4) + 8);
      case 0x59:
      case 0x79:
        *(int *)(param_1 + 0x2a8) = param_2;
      }
    }
    if (*(int *)(param_2 + 0x80) != 0) {
      FUN_005f01d0(*(undefined4 *)(param_2 + 0x80));
    }
    param_2 = *(int *)(param_2 + 0x7c);
  } while( true );
}

