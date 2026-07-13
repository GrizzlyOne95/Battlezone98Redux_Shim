
void FUN_00434bf0(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  
  if (((param_1 != 0) && (param_1 < 0x81)) && (param_1 != 0)) {
    iVar2 = param_1 + -1;
    uVar3 = iVar2 >> 0x1f;
    bVar1 = (byte)iVar2;
    if (param_2 == 0) {
      *(uint *)(&DAT_0260c234 + ((int)(iVar2 + (uVar3 & 0x1f)) >> 5) * 4) =
           1 << (bVar1 & 0x1f) | *(uint *)(&DAT_0260c234 + ((int)(iVar2 + (uVar3 & 0x1f)) >> 5) * 4)
      ;
    }
    else {
      if ((1 << (bVar1 & 0x1f) & *(uint *)(&DAT_0260c234 + ((int)(iVar2 + (uVar3 & 0x1f)) >> 5) * 4)
          ) != 0) {
        *(uint *)(&DAT_0260c234 + ((int)(iVar2 + (uVar3 & 0x1f)) >> 5) * 4) =
             ~(1 << (bVar1 & 0x1f)) &
             *(uint *)(&DAT_0260c234 + ((int)(iVar2 + (uVar3 & 0x1f)) >> 5) * 4);
      }
      *(uint *)(&DAT_0260c244 + ((int)(iVar2 + (uVar3 & 0x1f)) >> 5) * 4) =
           1 << (bVar1 & 0x1f) | *(uint *)(&DAT_0260c244 + ((int)(iVar2 + (uVar3 & 0x1f)) >> 5) * 4)
      ;
    }
    switch(param_1) {
    case 0x1d:
    case 0x70:
      if (param_2 == 0) {
        DAT_0260c240 = DAT_0260c240 | 0x800000;
      }
      else {
        if ((DAT_0260c240 & 0x800000) != 0) {
          DAT_0260c240 = DAT_0260c240 & 0xff7fffff;
        }
        DAT_0260c250 = DAT_0260c250 | 0x800000;
      }
      break;
    case 0x2a:
    case 0x36:
      if (param_2 == 0) {
        DAT_0260c240 = DAT_0260c240 | 0x400000;
      }
      else {
        if ((DAT_0260c240 & 0x400000) != 0) {
          DAT_0260c240 = DAT_0260c240 & 0xffbfffff;
        }
        DAT_0260c250 = DAT_0260c250 | 0x400000;
      }
      break;
    case 0x38:
    case 0x71:
      if (param_2 == 0) {
        DAT_0260c240 = DAT_0260c240 | 0x1000000;
      }
      else {
        if ((DAT_0260c240 & 0x1000000) != 0) {
          DAT_0260c240 = DAT_0260c240 & 0xfeffffff;
        }
        DAT_0260c250 = DAT_0260c250 | 0x1000000;
      }
    }
  }
  return;
}

