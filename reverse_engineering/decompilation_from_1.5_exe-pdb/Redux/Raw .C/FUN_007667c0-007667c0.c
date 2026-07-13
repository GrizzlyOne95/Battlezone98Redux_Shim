
void __fastcall FUN_007667c0(int param_1)

{
  int iVar1;
  
  do {
    switch(*(undefined4 *)(param_1 + 0x60)) {
    case 0:
      *(undefined4 *)(param_1 + 0x60) = 1;
      break;
    case 1:
      *(undefined4 *)(param_1 + 0x60) = 2;
      break;
    case 2:
      *(undefined4 *)(param_1 + 0x60) = 3;
      break;
    case 3:
      *(undefined4 *)(param_1 + 0x60) = 4;
      break;
    case 4:
      *(undefined4 *)(param_1 + 0x60) = 0;
      break;
    default:
      *(undefined4 *)(param_1 + 0x60) = 0;
    }
    iVar1 = FUN_00766f80();
  } while (iVar1 == 0);
  *(undefined4 *)(param_1 + 0x3c) = 0;
  return;
}

