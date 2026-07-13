/*
 * Entry: 0054f1fb
 * Name: OpenMemoryMapFile
 * Namespace: Global
 * Signature: MM_HANDLE * OpenMemoryMapFile(MM_HANDLE * __return_storage_ptr__, char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

MM_HANDLE * __cdecl OpenMemoryMapFile(MM_HANDLE *__return_storage_ptr__,char *param_1,char *param_2)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  HANDLE pvVar6;
  uint uVar7;
  CHAR local_88 [128];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  __return_storage_ptr__->File = (void *)0x0;
  __return_storage_ptr__->Map = (void *)0x0;
  __return_storage_ptr__->Buffer = (char *)0x0;
  pcVar4 = param_1;
  if (param_2 == (char *)0x0) {
    local_88[0] = '\0';
  }
  else {
    iVar3 = -(int)param_2;
    do {
      cVar2 = *param_2;
      param_2[(int)(local_88 + iVar3)] = cVar2;
      param_2 = param_2 + 1;
    } while (cVar2 != '\0');
  }
  do {
    cVar2 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar2 != '\0');
  uVar5 = (int)pcVar4 - (int)param_1;
  pcVar4 = &stack0xffffff77;
  do {
    pcVar1 = pcVar4 + 1;
    pcVar4 = pcVar4 + 1;
  } while (*pcVar1 != '\0');
  for (uVar7 = uVar5 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar4 = *(undefined4 *)param_1;
    param_1 = param_1 + 4;
    pcVar4 = pcVar4 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar4 = *param_1;
    param_1 = param_1 + 1;
    pcVar4 = pcVar4 + 1;
  }
  pvVar6 = CreateFileA(local_88,0xc0000000,3,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
  __return_storage_ptr__->File = pvVar6;
  if (pvVar6 != (HANDLE)0xffffffff) {
    pvVar6 = CreateFileMappingA(pvVar6,(LPSECURITY_ATTRIBUTES)0x0,4,0,0,(LPCSTR)0x0);
    __return_storage_ptr__->Map = pvVar6;
    if (pvVar6 != (HANDLE)0x0) {
      pcVar4 = MapViewOfFile(pvVar6,6,0,0,0);
      __return_storage_ptr__->Buffer = pcVar4;
      if (pcVar4 != (char *)0x0) {
        return __return_storage_ptr__;
      }
    }
  }
  CloseMemoryMapFile(__return_storage_ptr__);
  DEBUG_systemError("Can\'t open file %s");
  return __return_storage_ptr__;
}
