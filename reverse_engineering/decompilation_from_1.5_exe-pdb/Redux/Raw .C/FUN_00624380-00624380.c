
void FUN_00624380(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_c;
  short local_8;
  
  DAT_02ceb882 = 0xfffa;
  DAT_00920164 = 1;
  sprintf(&DAT_02ceb860,"%s: ",DAT_02ceb84c);
  (&DAT_02ceb882)[DAT_00920164 * 0x12] = 0xfff9;
  iVar2 = DAT_00920164 * 0x24;
  DAT_00920164 = DAT_00920164 + 1;
  sprintf(&DAT_02ceb860 + iVar2,"%s: ",DAT_02cebc98);
  local_8 = FUN_00577bd0(&local_c,0,0,0);
  for (; (local_8 != 0 && (DAT_00920164 < 0x1e)); DAT_00920164 = DAT_00920164 + 1) {
    uVar1 = FUN_00577a00(local_8);
    sprintf(&DAT_02ceb860 + DAT_00920164 * 0x24,"%s %s (#%d): ",DAT_02ceb854,local_c,uVar1);
    (&DAT_02ceb882)[DAT_00920164 * 0x12] = local_8;
    local_8 = FUN_00577c90(local_8,&local_c,0,0,0);
  }
  if ((int)DAT_00920164 <= DAT_0092016c) {
    DAT_0092016c = 0;
  }
  FUN_00823470(DAT_02a1748c,&DAT_02ceb860 + DAT_0092016c * 0x24);
  FUN_00823600(DAT_02a1748c,&DAT_008a1ad8);
  FUN_00823330(DAT_02a1748c,1);
  FUN_00434f20();
  FUN_00823390(DAT_02a1748c,1);
  FUN_00821310(DAT_00920168,1,0);
  return;
}

