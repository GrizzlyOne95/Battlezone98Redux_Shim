/*
 * Entry: 005490d4
 * Name: in_sptr
 * Namespace: Global
 * Signature: bool in_sptr(_iobuf * param_1, void * * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl in_sptr(_iobuf *param_1,void **param_2,uint param_3)

{
  char *pcVar1;
  bool bVar2;
  int iVar3;
  void *unaff_retaddr;
  
  if (binarySave) {
    bVar2 = in_data(8,(long)param_2,unaff_retaddr);
    return bVar2;
  }
  in_prep();
  iVar3 = sscanf(inCurrent,"%*s = %p",param_2);
  pcVar1 = nextLine;
  *nextLine = '\r';
  inCurrent = pcVar1 + 2;
  return (bool)('\x01' - (iVar3 != 1));
}
