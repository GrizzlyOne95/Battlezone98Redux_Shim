/*
 * Entry: 004f9d24
 * Name: Read_Scan_Line
 * Namespace: Global
 * Signature: void Read_Scan_Line(_iobuf * param_1, char * param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Read_Scan_Line(_iobuf *param_1,char *param_2,long param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = 0;
  if (0 < param_3) {
    do {
      iVar1 = fgetc((FILE *)param_1);
      if (iVar1 < 0xc1) {
        param_2[iVar3] = (char)iVar1;
        iVar3 = iVar3 + 1;
      }
      else {
        iVar4 = iVar1 + -0xc0;
        iVar2 = fgetc((FILE *)param_1);
        memset(param_2 + iVar3,iVar2,iVar4);
        iVar3 = iVar3 + iVar1 + -0xc0;
      }
    } while (iVar3 < param_3);
  }
  return;
}
