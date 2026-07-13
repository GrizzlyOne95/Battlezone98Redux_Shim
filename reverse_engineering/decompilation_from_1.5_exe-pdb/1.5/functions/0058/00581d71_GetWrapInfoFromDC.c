/*
 * Entry: 00581d71
 * Name: GetWrapInfoFromDC
 * Namespace: Global
 * Signature: WRAP_INFO * GetWrapInfoFromDC(WRAP_INFO * __return_storage_ptr__, char * param_1, long param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WRAP_INFO * __cdecl
GetWrapInfoFromDC(WRAP_INFO *__return_storage_ptr__,char *param_1,long param_2,void *param_3)

{
  char cVar1;
  WRAP_INFO *pWVar2;
  char *pcVar3;
  BOOL BVar4;
  long lVar5;
  WRAP_INFO *pWVar6;
  char *pcVar7;
  tagSIZE local_c;
  
  pcVar7 = param_1;
  pWVar2 = __return_storage_ptr__;
  __return_storage_ptr__->NumChars = 0;
  pcVar3 = param_1;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  BVar4 = GetTextExtentExPointA
                    (param_3,param_1,(int)pcVar3 - (int)(param_1 + 1),param_2,
                     (LPINT)&__return_storage_ptr__,(LPINT)0x0,&local_c);
  pWVar6 = __return_storage_ptr__;
  if (BVar4 != 0) {
    __return_storage_ptr__ = (WRAP_INFO *)0x0;
    pWVar2->NextStr = pcVar7;
    pWVar2->NumBytes = (long)pWVar6;
    while (pWVar6 != (WRAP_INFO *)0x0) {
      pWVar6 = (WRAP_INFO *)((int)&pWVar6[-1].NextStr + 3);
      if ((*pcVar7 == '\r') && (pcVar7[1] == '\n')) {
        __return_storage_ptr__ = (WRAP_INFO *)((int)&__return_storage_ptr__->NumChars + 1);
        pWVar2->NumBytes = (int)pcVar7 - (int)pWVar2->NextStr;
        pcVar7 = pcVar7 + 2;
        break;
      }
      lVar5 = isMBC(*pcVar7);
      if (lVar5 == 0) {
        __return_storage_ptr__ = (WRAP_INFO *)((int)&__return_storage_ptr__->NumChars + 1);
      }
      pcVar7 = pcVar7 + 1;
    }
    pWVar2->NumChars = (long)__return_storage_ptr__;
    pWVar2->NextStr = pcVar7;
  }
  return pWVar2;
}
