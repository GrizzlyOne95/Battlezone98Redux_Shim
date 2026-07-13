/*
 * Entry: 004a0618
 * Name: GetFloat
 * Namespace: Global
 * Signature: float GetFloat(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Enum "LOCALE": Some values do not have unique names */

float __cdecl GetFloat(char *param_1)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  char *unaff_EDI;
  float local_10c;
  char local_108 [124];
  undefined1 local_8c [132];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_8c;
  if (LocaleInfo->Locale != LOCALE_ENGLISH) {
    pcVar2 = setlocale(0,(char *)0x0);
    pcVar3 = local_108;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
      *pcVar3 = cVar1;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    setlocale(0,"English");
  }
  sscanf(unaff_EDI,"%f",&local_10c);
  if (LocaleInfo->Locale != LOCALE_ENGLISH) {
    setlocale(0,local_108);
  }
  return local_10c;
}
