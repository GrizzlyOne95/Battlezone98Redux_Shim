
ushort FUN_00784100(uint param_1,uint param_2)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = (param_2 & 0xff) * 0x100 + (param_1 & 0xff);
  iVar2 = ((int)param_2 >> 8) * 0x80 + ((int)param_1 >> 8) + 0xc18;
  if ((iVar2 < 0) || (0x3fff < iVar2)) {
    uVar1 = *(ushort *)(DAT_02cc5104 + iVar3 * 2);
  }
  else {
    uVar1 = *(ushort *)(*(int *)(&DAT_02cc5108 + iVar2 * 4) + iVar3 * 2);
  }
  return uVar1 & 0xfff;
}

