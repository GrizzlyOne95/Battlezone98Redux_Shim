
ushort FUN_00785f50(int param_1,int param_2,int param_3,uint param_4,uint param_5)

{
  ushort uVar1;
  
  if ((int)param_4 < param_2 * 0x80) {
    if ((int)param_5 < param_3 * 0x80) {
      uVar1 = *(ushort *)
               (param_1 +
               ((param_5 & 0x7f) * 0x80 + (param_4 & 0x7f) +
                ((int)(param_4 - (param_4 & 0x7f)) >> 7) * 0x4000 +
               ((int)(param_5 - (param_5 & 0x7f)) >> 7) * param_2 * 0x4000) * 2) & 0xfff;
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

