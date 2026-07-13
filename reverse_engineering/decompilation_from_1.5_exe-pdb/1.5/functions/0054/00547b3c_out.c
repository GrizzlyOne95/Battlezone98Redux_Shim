/*
 * Entry: 00547b3c
 * Name: out
 * Namespace: Global
 * Signature: bool out(_iobuf * param_1, bool * param_2, uint param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl out(_iobuf *param_1,bool *param_2,uint param_3,char *param_4)

{
  bool bVar1;
  char *pcVar2;
  void *unaff_EDI;
  int iVar3;
  
  if (binarySave) {
    bVar1 = out_data(param_1,1,(long)param_2,unaff_EDI);
  }
  else {
    fprintf((FILE *)param_1,"%s [%d] =\r\n",param_4,param_3);
    iVar3 = 0;
    if (0 < (int)param_3) {
      do {
        pcVar2 = "true";
        if (param_2[iVar3] == false) {
          pcVar2 = "false";
        }
        fprintf((FILE *)param_1,"%s\r\n",pcVar2);
        iVar3 = iVar3 + 1;
      } while (iVar3 < (int)param_3);
    }
    bVar1 = true;
  }
  return bVar1;
}
