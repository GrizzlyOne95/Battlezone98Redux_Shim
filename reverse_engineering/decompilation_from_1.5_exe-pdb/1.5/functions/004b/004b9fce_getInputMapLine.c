/*
 * Entry: 004b9fce
 * Name: getInputMapLine
 * Namespace: Global
 * Signature: int getInputMapLine(char * param_1, int param_2, _iobuf * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl getInputMapLine(char *param_1,int param_2,_iobuf *param_3)

{
  bool bVar1;
  int iVar2;
  char *pcVar3;
  
  bVar1 = false;
  do {
    do {
      pcVar3 = fgets(param_1,param_2,(FILE *)param_3);
      if (pcVar3 == (char *)0x0) {
        return 0;
      }
      pcVar3 = param_1;
    } while (*param_1 == '\0');
    do {
      if (*pcVar3 == '\n') {
        *pcVar3 = '\0';
        break;
      }
      iVar2 = isspace((int)*pcVar3);
      if (iVar2 == 0) {
        bVar1 = true;
      }
      pcVar3 = pcVar3 + 1;
    } while (*pcVar3 != '\0');
    if (bVar1) {
      return 1;
    }
  } while( true );
}
