
void __fastcall FUN_005981a0(int param_1)

{
  if (*(int *)(param_1 + 0x78) != -1) {
    switch(*(undefined4 *)(param_1 + 0x74)) {
    case 0:
      FUN_00598340();
      break;
    case 1:
      FUN_00598930();
      break;
    case 2:
      FUN_00417c60();
      break;
    case 3:
      FUN_00417c60();
    }
    *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x78);
    *(undefined4 *)(param_1 + 0x78) = 0xffffffff;
    switch(*(undefined4 *)(param_1 + 0x74)) {
    case 0:
      FUN_005982c0();
      break;
    case 1:
      FUN_00598910();
      break;
    case 2:
      FUN_00599740();
      break;
    case 3:
      FUN_0059ada0();
    }
  }
  switch(*(undefined4 *)(param_1 + 0x74)) {
  case 0:
    FUN_005983a0();
    break;
  case 1:
    FUN_00598960();
    break;
  case 2:
    FUN_0059a010();
    break;
  case 3:
    FUN_0059add0();
  }
  return;
}

