/*
 * Entry: 00547a0a
 * Name: out_data
 * Namespace: Global
 * Signature: bool out_data(_iobuf * param_1, long param_2, long param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl out_data(_iobuf *param_1,long param_2,long param_3,void *param_4)

{
  char cVar1;
  size_t sVar2;
  size_t unaff_EDI;
  
  param_2 = CONCAT22((short)unaff_EDI,(undefined2)param_2);
  sVar2 = fwrite(&param_2,1,4,(FILE *)param_1);
  if (sVar2 == 4) {
    sVar2 = fwrite((void *)param_3,1,unaff_EDI,(FILE *)param_1);
    cVar1 = '\x01' - (sVar2 != unaff_EDI);
  }
  else {
    cVar1 = '\0';
  }
  return (bool)cVar1;
}
