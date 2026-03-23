
uint FUN_00583e70(uint param_1,uint param_2)

{
  uint uVar1;
  uint local_8;
  
  local_8 = 0;
  uVar1 = param_1 & 0x7f7f7f7f;
  while( true ) {
    if (0x16 < local_8) {
      return uVar1 & 0xffffff00;
    }
    if (((param_1 & 0x7f7f7f7f) == *(uint *)(&DAT_02a13bb8 + local_8 * 8)) &&
       ((param_2 & 0x7f7f7f7f) == *(uint *)(&DAT_02a13bbc + local_8 * 8))) break;
    uVar1 = local_8;
    local_8 = local_8 + 1;
  }
  return local_8 + 0x80;
}

