
undefined4 * __thiscall
FUN_007ccb70(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,uint param_7,undefined4 param_8)

{
  FUN_007d1cc0(param_2,param_3,param_4,param_5,param_6,param_7 | 0x20,param_8,0);
  *param_1 = cUI_TextBlock::vftable;
  param_1[0xa51] = 0x3f400000;
  param_1[0xa52] = 0;
  memset(param_1 + 0x51,0,0x2800);
  param_1[0x40] = 0xff000000;
  return param_1;
}

