/*
 * Entry: 00549c4c
 * Name: in_ptr
 * Namespace: Global
 * Signature: bool in_ptr(_iobuf * param_1, void * * param_2, uint param_3, char * param_4, void * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl in_ptr(_iobuf *param_1,void **param_2,uint param_3,char *param_4,void *param_5)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  Addr *pAVar4;
  void *unaff_EBP;
  
  if (binarySave) {
    cVar2 = in_data(8,(long)param_2,unaff_EBP);
  }
  else {
    in_prep();
    iVar3 = sscanf(inCurrent,"%*s = %p",param_2);
    pcVar1 = nextLine;
    cVar2 = '\x01' - (iVar3 != 1);
    *nextLine = '\r';
    inCurrent = pcVar1 + 2;
  }
  if (cVar2 != '\0') {
    pAVar4 = operator_new(0x10);
    if (pAVar4 == (Addr *)0x0) {
      pAVar4 = (Addr *)0x0;
    }
    else {
      pAVar4 = Addr::Addr(pAVar4,param_2,*param_2,param_4,param_5);
    }
    if (pAVar4 != (Addr *)0x0) {
      return true;
    }
  }
  return false;
}
