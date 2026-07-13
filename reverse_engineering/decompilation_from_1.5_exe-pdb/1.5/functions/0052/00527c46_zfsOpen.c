/*
 * Entry: 00527c46
 * Name: zfsOpen
 * Namespace: Global
 * Signature: ZFS_COOKIE * zfsOpen(char * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ZFS_COOKIE * __cdecl zfsOpen(char *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  char *pcVar3;
  ZFS_COOKIE *pZVar4;
  _iobuf *unaff_ESI;
  char *unaff_EDI;
  
  if (param_2 == 0) {
    param_2 = (int)fopen(param_1,"rb");
    if ((FILE *)param_2 == (FILE *)0x0) goto LAB_00527cbb;
    setvbuf((FILE *)param_2,(char *)0x0,4,0);
  }
  else {
    param_2 = (int)fopen(param_1,"rb+");
    if ((FILE *)param_2 != (FILE *)0x0) goto LAB_00527cd1;
    piVar1 = _errno();
    if ((*piVar1 != 2) || (iVar2 = zfsCreateFile(param_1,0), iVar2 == 0)) goto LAB_00527cbb;
    param_2 = (int)fopen(param_1,"rb+");
  }
  if (param_2 != 0) {
LAB_00527cd1:
    pcVar3 = strrchr(param_1,0x2f);
    if (pcVar3 != (char *)0x0) {
      param_1 = pcVar3 + 1;
    }
    strrchr(param_1,0x5c);
    pZVar4 = buildcookie(unaff_EDI,unaff_ESI);
    if (pZVar4 == (ZFS_COOKIE *)0x0) {
      fclose((FILE *)param_2);
      return (ZFS_COOKIE *)0x0;
    }
    return pZVar4;
  }
LAB_00527cbb:
  sprintf(&zfserr,"Could not open file \"%s\"",param_1);
  return (ZFS_COOKIE *)0x0;
}
