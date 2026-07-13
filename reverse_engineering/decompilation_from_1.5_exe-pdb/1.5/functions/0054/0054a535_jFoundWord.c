/*
 * Entry: 0054a535
 * Name: jFoundWord
 * Namespace: Global
 * Signature: WRAP_INFO * jFoundWord(WRAP_INFO * __return_storage_ptr__, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WRAP_INFO * __cdecl jFoundWord(WRAP_INFO *__return_storage_ptr__,char *param_1)

{
  char cVar1;
  char *pcVar2;
  bool bVar3;
  long lVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  
  pcVar2 = param_1;
  iVar7 = 0;
  bVar3 = false;
  __return_storage_ptr__->NumBytes = 0;
  if (param_1 != (char *)0x0) {
    param_1 = (char *)0x0;
    cVar1 = *pcVar2;
    while ((cVar1 != '\0' && (!bVar3))) {
      lVar4 = isMBC(*pcVar2);
      param_1 = param_1 + 1;
      iVar7 = iVar7 + 1 + lVar4;
      pcVar5 = jGetNextCharacter(pcVar2);
      iVar6 = jCanEndHere(pcVar2,pcVar5);
      if (iVar6 != 0) {
        bVar3 = true;
      }
      cVar1 = *pcVar5;
      pcVar2 = pcVar5;
    }
    __return_storage_ptr__->NumBytes = iVar7;
    __return_storage_ptr__->NumChars = (long)param_1;
    __return_storage_ptr__->NextStr = pcVar2;
  }
  return __return_storage_ptr__;
}
