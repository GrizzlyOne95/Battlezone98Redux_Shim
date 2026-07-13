
undefined4 * __thiscall
FUN_007cc390(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
            undefined4 param_9)

{
  undefined4 uVar1;
  
  uVar1 = FUN_007cc360(param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  FUN_007d1cc0(uVar1,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  *param_1 = cUI_Text::vftable;
  param_1[0x245] = 0;
  param_1[0x246] = 0;
  param_1[0x247] = 0xff00ff00;
  param_1[0x248] = 0x3f800000;
  param_1[0x249] = 0;
  param_1[0x24a] = 0;
  *(undefined1 *)(param_1 + 0x24b) = 1;
  *(undefined1 *)((int)param_1 + 0x92d) = 0;
  if ((param_1[5] & 0x8000) == 0) {
    if ((param_1[5] & 0x10000) == 0) {
      if ((param_1[5] & 0x4000) != 0) {
        param_1[0x245] = 0;
      }
    }
    else {
      param_1[0x245] = 2;
    }
  }
  else {
    param_1[0x245] = 1;
  }
  if ((param_1[5] & 0x1000) == 0) {
    if ((param_1[5] & 0x2000) == 0) {
      if ((param_1[5] & 0x800) != 0) {
        param_1[0x246] = 0;
      }
    }
    else {
      param_1[0x246] = 1;
    }
  }
  else {
    param_1[0x246] = 2;
  }
  memset(param_1 + 0x51,0,2000);
  return param_1;
}

