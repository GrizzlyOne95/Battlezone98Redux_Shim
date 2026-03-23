
void __fastcall FUN_00614d50(int param_1)

{
  switch(*(undefined4 *)(param_1 + 8)) {
  case 1:
    *(undefined4 *)(param_1 + 8) = 5;
  case 5:
    *(undefined4 *)(param_1 + 0xf0) = 0x42960000;
    FUN_00605350();
    break;
  case 2:
    FUN_00601070();
    break;
  case 3:
    FUN_006028d0();
  }
  return;
}

