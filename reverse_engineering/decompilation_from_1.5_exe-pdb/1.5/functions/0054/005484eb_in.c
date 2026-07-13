/*
 * Entry: 005484eb
 * Name: in
 * Namespace: Global
 * Signature: bool in(_iobuf * param_1, char * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl in(_iobuf *param_1,char *param_2,uint param_3)

{
  char *pcVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  void *unaff_retaddr;
  
  if (binarySave) {
    bVar2 = in_data(2,(long)param_2,unaff_retaddr);
    return bVar2;
  }
  in_prep();
  iVar4 = sscanf(inCurrent,"%*s = %[^\n]s",param_2);
  cVar3 = -(iVar4 != 1) + '\x01';
  if (cVar3 == '\0') {
    *param_2 = '\0';
    cVar3 = -(iVar4 != 1) + '\x02';
  }
  pcVar1 = nextLine;
  *nextLine = '\r';
  inCurrent = pcVar1 + 2;
  return (bool)cVar3;
}
