
float10 __thiscall FUN_005e6af0(int param_1,float param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  float10 fVar3;
  float local_14;
  
  local_14 = param_2;
  fVar3 = (float10)FUN_00822d80();
  if (param_2 < (float)fVar3) {
    fVar3 = (float10)FUN_00822d80();
    local_14 = (float)fVar3 + 15.0;
    iVar1 = FUN_004f2de0();
    if (iVar1 == 0) {
      switch(param_3) {
      case 1:
        uVar2 = FUN_00437d30("tran0202.wav");
        *(undefined4 *)(param_1 + 0xa8) = uVar2;
        break;
      case 2:
        uVar2 = FUN_00437d30("tran0203.wav");
        *(undefined4 *)(param_1 + 0xa8) = uVar2;
        break;
      case 3:
        uVar2 = FUN_00437d30("tran0202.wav");
        *(undefined4 *)(param_1 + 0xa8) = uVar2;
        break;
      case 4:
        uVar2 = FUN_00437d30("tran0211.wav");
        *(undefined4 *)(param_1 + 0xa8) = uVar2;
        break;
      case 5:
        uVar2 = FUN_00437d30("tran0206.wav");
        *(undefined4 *)(param_1 + 0xa8) = uVar2;
        break;
      case 6:
        uVar2 = FUN_00437d30("misn0109.wav");
        *(undefined4 *)(param_1 + 0xa8) = uVar2;
        break;
      case 7:
        uVar2 = FUN_00437d30("tran0207.wav");
        *(undefined4 *)(param_1 + 0xa8) = uVar2;
        break;
      case 8:
        uVar2 = FUN_00437d30("tran0208.wav");
        *(undefined4 *)(param_1 + 0xa8) = uVar2;
        local_14 = 99999.0;
      }
    }
    else {
      switch(param_3) {
      case 1:
        FUN_004f49c0(0x10);
        break;
      case 2:
        uVar2 = FUN_00437d30("tran0203.wav");
        *(undefined4 *)(param_1 + 0xa8) = uVar2;
        FUN_004f49c0(0x11);
        break;
      case 3:
        FUN_004f49c0(0x10);
        break;
      case 4:
        FUN_004f49c0(0x1a);
        break;
      case 5:
        FUN_004f49c0(0x13);
        break;
      case 6:
        FUN_004f49c0(7);
        uVar2 = FUN_00437d30("misn0109.wav");
        *(undefined4 *)(param_1 + 0xa8) = uVar2;
        break;
      case 7:
        FUN_004f49c0(0x14);
        break;
      case 8:
        FUN_004f49c0(0x15);
        local_14 = 99999.0;
      }
    }
  }
  return (float10)local_14;
}

