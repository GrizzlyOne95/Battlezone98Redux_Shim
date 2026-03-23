
void __fastcall FUN_004d3a90(int param_1)

{
  char cVar1;
  
  switch(*(undefined4 *)(param_1 + 8)) {
  case 1:
    *(undefined4 *)(param_1 + 0xc) = 4;
    break;
  case 2:
    FUN_00601070();
    break;
  case 3:
    FUN_006028d0();
    break;
  case 4:
    if ((*(int *)(param_1 + 0x11c) != 0) &&
       (cVar1 = FUN_004d35b0(*(undefined4 *)(param_1 + 0x10)), cVar1 != '\0')) {
      FUN_004d39f0();
      FUN_004d3630(*(undefined4 *)(param_1 + 0x10));
    }
  }
  return;
}

