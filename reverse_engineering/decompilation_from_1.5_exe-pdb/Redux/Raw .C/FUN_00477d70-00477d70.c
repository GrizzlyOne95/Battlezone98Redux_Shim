
undefined4 FUN_00477d70(int param_1)

{
  undefined4 uVar1;
  
  switch(*(undefined4 *)(param_1 + 0x84)) {
  case 2:
  case 5:
  case 7:
  case 10:
    uVar1 = 1;
    break;
  default:
    uVar1 = 0;
  }
  return uVar1;
}

