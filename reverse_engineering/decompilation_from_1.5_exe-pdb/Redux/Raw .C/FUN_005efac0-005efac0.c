
void __fastcall FUN_005efac0(int param_1)

{
  undefined4 uVar1;
  
  switch(*(undefined4 *)(param_1 + 0x1c)) {
  case 2:
    *(undefined4 *)(param_1 + 0x28) = 0xf149f2ca;
    break;
  case 3:
  case 4:
  case 9:
    uVar1 = FUN_004dc010();
    uVar1 = FUN_00477590(uVar1);
    *(undefined4 *)(param_1 + 0x30) = uVar1;
    break;
  case 6:
    *(undefined4 *)(param_1 + 0x28) = 0xf149f2ca;
  }
  return;
}

