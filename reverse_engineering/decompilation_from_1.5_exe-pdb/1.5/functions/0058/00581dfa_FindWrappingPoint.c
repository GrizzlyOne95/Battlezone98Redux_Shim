/*
 * Entry: 00581dfa
 * Name: FindWrappingPoint
 * Namespace: Global
 * Signature: WRAP_INFO * FindWrappingPoint(WRAP_INFO * __return_storage_ptr__, char * param_1, long param_2, _func___cdecl_WRAP_INFO_char_ptr_long_void_ptr * param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WRAP_INFO * __cdecl
FindWrappingPoint(WRAP_INFO *__return_storage_ptr__,char *param_1,long param_2,
                 _func___cdecl_WRAP_INFO_char_ptr_long_void_ptr *param_3,void *param_4)

{
  WRAP_INFO *pWVar1;
  int iVar2;
  WRAP_INFO local_28;
  long local_1c;
  long lStack_18;
  char *local_14;
  WRAP_INFO local_10;
  
  __return_storage_ptr__->NumBytes = 0;
  __return_storage_ptr__->NumChars = 0;
  if (*param_1 != '\0') {
    pWVar1 = (*param_3)(&local_10,param_1,param_2,param_4);
    local_1c = pWVar1->NumChars;
    lStack_18 = pWVar1->NumBytes;
    local_14 = pWVar1->NextStr;
    if (*local_14 != '\0') {
      while( true ) {
        if ((*param_1 == '\r') && (param_1[1] == '\n')) {
          local_10.NumBytes = 0;
          param_1 = param_1 + 2;
          local_10.NumChars = 1;
        }
        else {
          pWVar1 = jFoundWord(&local_28,param_1);
          local_10.NumChars = pWVar1->NumChars;
          local_10.NumBytes = pWVar1->NumBytes;
          param_1 = pWVar1->NextStr;
          if (local_10.NumChars == 0) {
            return __return_storage_ptr__;
          }
        }
        iVar2 = __return_storage_ptr__->NumChars + local_10.NumChars;
        if (local_1c < iVar2) break;
        __return_storage_ptr__->NumChars = iVar2;
        __return_storage_ptr__->NumBytes = __return_storage_ptr__->NumBytes + local_10.NumBytes;
        __return_storage_ptr__->NextStr = param_1;
        local_10.NextStr = param_1;
      }
      return __return_storage_ptr__;
    }
    __return_storage_ptr__->NumChars = pWVar1->NumChars;
    __return_storage_ptr__->NumBytes = pWVar1->NumBytes;
    __return_storage_ptr__->NextStr = pWVar1->NextStr;
  }
  return __return_storage_ptr__;
}
