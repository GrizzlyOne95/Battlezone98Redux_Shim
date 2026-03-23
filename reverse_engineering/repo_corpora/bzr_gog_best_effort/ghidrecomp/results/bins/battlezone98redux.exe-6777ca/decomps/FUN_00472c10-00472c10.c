
uint __thiscall FUN_00472c10(uint param_1,uint param_2)

{
  uint in_EAX;
  uint3 uVar2;
  undefined4 uVar1;
  
  if (param_2 == 0x16) {
    *(undefined4 *)(param_1 + 0x378) = 0;
    param_1 = param_1 & 0xffffff00;
  }
  else if (param_2 == 0x12) {
    *(undefined4 *)(param_1 + 0x378) = 1;
    param_1 = in_EAX & 0xffffff00;
  }
  else {
    uVar2 = (uint3)(in_EAX >> 8);
    if (param_2 == 0x13) {
      *(undefined4 *)(param_1 + 0x378) = 2;
      param_1 = (uint)uVar2 << 8;
    }
    else if (param_2 == 0x14) {
      *(undefined4 *)(param_1 + 0x378) = 3;
      param_1 = param_1 & 0xffffff00;
    }
    else if (param_2 == 0x15) {
      *(undefined4 *)(param_1 + 0x378) = 4;
      param_1 = (uint)uVar2 << 8;
    }
    else if (param_2 < 0x1b) {
      param_1 = FUN_005aeab0(param_2);
    }
    else {
      FUN_004dbf90(0x15,param_2,0);
      uVar1 = FUN_00472370(param_2);
      param_1 = FUN_004723b0(uVar1);
      param_1 = param_1 & 0xffffff00;
    }
  }
  return param_1;
}

