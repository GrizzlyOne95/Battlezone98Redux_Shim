
undefined4 __thiscall FUN_0062a5d0(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  if ((param_2 < 0) || (0x1ff < param_2)) {
    FUN_007d6c70("AnimObj_Stop - Requested to stop invalid Animation %d\n",param_2,param_1);
    uVar1 = 0xffffffff;
  }
  else {
    if (DAT_00920c58 < 1) {
      DAT_00920c58 = 0;
    }
    else {
      DAT_00920c58 = DAT_00920c58 + -1;
    }
    param_2 = param_2 * 0x20;
    *(undefined4 *)(&DAT_02a17498 + param_2) = 0;
    *(undefined4 *)(&DAT_02a1749c + param_2) = 0;
    *(undefined4 *)(&DAT_02a174a0 + param_2) = 0;
    *(undefined4 *)(&DAT_02a174a4 + param_2) = 0;
    *(undefined4 *)(&DAT_02a174a8 + param_2) = 0;
    *(undefined4 *)(&DAT_02a174ac + param_2) = 0;
    *(undefined4 *)(&DAT_02a174b0 + param_2) = 0;
    *(undefined4 *)(&DAT_02a174b4 + param_2) = 0;
    uVar1 = 0;
  }
  return uVar1;
}

