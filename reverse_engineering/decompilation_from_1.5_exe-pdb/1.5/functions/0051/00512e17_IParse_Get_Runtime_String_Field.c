/*
 * Entry: 00512e17
 * Name: IParse_Get_Runtime_String_Field
 * Namespace: Global
 * Signature: char * IParse_Get_Runtime_String_Field(void * param_1, char * param_2, int * param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

char * __cdecl
IParse_Get_Runtime_String_Field(void *param_1,char *param_2,int *param_3,char *param_4)

{
  char cVar1;
  char *_Source;
  char *pcVar2;
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  _Source = IParse_Get_Runtime_Struct_Field(param_1,param_2);
  if (_Source == (char *)0x0) {
    *param_3 = -1;
    sprintf(local_108,"Config or AIP string parameter \'%s\' not found.",param_2);
    param_4 = (char *)0x0;
  }
  else {
    pcVar2 = _Source;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    strncpy(param_4,_Source,(size_t)(pcVar2 + (1 - (int)(_Source + 1))));
    *param_3 = 0;
  }
  return param_4;
}
