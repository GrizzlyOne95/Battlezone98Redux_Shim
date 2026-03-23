
uint FUN_0068ac50(uint param_1,uint param_2)

{
  switch(param_2 & 7) {
  case 2:
    param_1 = ((param_1 >> 0x18) * 0xa0) / 0xff << 0x18 | param_1 & 0xffffff;
    break;
  case 3:
    param_1 = ((param_1 >> 0x18) * 0x60) / 0xff << 0x18 | param_1 & 0xffffff;
    break;
  case 4:
    break;
  case 5:
    param_1 = DAT_00920ef8;
  }
  return param_1;
}

