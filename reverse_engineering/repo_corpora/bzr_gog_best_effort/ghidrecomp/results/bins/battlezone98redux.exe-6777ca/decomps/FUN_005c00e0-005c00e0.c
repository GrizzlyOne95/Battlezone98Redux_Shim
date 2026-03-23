
void __fastcall FUN_005c00e0(int param_1)

{
  switch(*(undefined4 *)(param_1 + 8)) {
  case 1:
    *(undefined4 *)(param_1 + 8) = 5;
  case 5:
    FUN_005bf870(*(undefined4 *)(param_1 + 0x10));
    break;
  case 2:
    FUN_005bf850(*(undefined4 *)(param_1 + 0x10));
    FUN_00601070();
    break;
  case 3:
    FUN_006028d0();
  }
  return;
}

