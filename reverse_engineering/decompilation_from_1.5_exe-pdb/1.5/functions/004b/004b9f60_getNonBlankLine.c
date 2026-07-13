/*
 * Entry: 004b9f60
 * Name: getNonBlankLine
 * Namespace: Global
 * Signature: int getNonBlankLine(char * param_1, int param_2, _iobuf * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl getNonBlankLine(char *param_1,int param_2,_iobuf *param_3)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  char *pcVar4;
  byte *pbVar5;
  
  bVar2 = false;
  do {
    do {
      pcVar4 = fgets(param_1,param_2,(FILE *)param_3);
      if (pcVar4 == (char *)0x0) {
        return 0;
      }
      inmap_lineno = inmap_lineno + 1;
      pbVar5 = (byte *)param_1;
    } while (*param_1 == '\0');
    do {
      bVar1 = *pbVar5;
      if ((bVar1 == 10) || (bVar1 == 0x23)) {
        *pbVar5 = 0;
        break;
      }
      iVar3 = isspace((uint)bVar1);
      if (iVar3 == 0) {
        bVar2 = true;
      }
      pbVar5 = pbVar5 + 1;
    } while (*pbVar5 != 0);
    if (bVar2) {
      return 1;
    }
  } while( true );
}
