
void FUN_00783200(ushort *param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_10;
  uint local_8;
  
  local_8 = (uint)*param_1;
  iVar5 = (int)(local_8 & 0xf000) >> 0xc;
  iVar2 = (int)(local_8 & 0xf00) >> 8;
  iVar4 = (int)(local_8 & 0x80) >> 7;
  local_8 = local_8 & 3;
  bVar1 = (&DAT_02c06778)[iVar4 + local_8 * 2 + iVar2 * 8 + iVar5 * 0x40];
  local_10 = 0;
  while( true ) {
    if (3 < local_10) {
      return;
    }
    local_8 = local_8 + param_2;
    if (3 < (int)local_8) {
      local_8 = 0;
    }
    if ((int)local_8 < 0) {
      local_8 = 3;
    }
    if (((byte)(&DAT_02c06778)[iVar4 + local_8 * 2 + iVar2 * 8 + iVar5 * 0x40] != 0) &&
       (iVar3 = _strnicmp(&DAT_02c069d0 +
                          (uint)(byte)(&DAT_02c06778)
                                      [iVar4 + local_8 * 2 + iVar2 * 8 + iVar5 * 0x40] * 0x10,
                          &DAT_02c069d0 + (uint)bVar1 * 0x10,0x10), iVar3 != 0)) break;
    local_10 = local_10 + 1;
  }
  *param_1 = *param_1 & 0xfffc | (ushort)local_8 & 3;
  return;
}

