/*
 * Entry: 0054bb87
 * Name: GetShellLocaleInfo
 * Namespace: Global
 * Signature: LOCALE_INFO * GetShellLocaleInfo(long * param_1, long * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Enum "LOCALE": Some values do not have unique names */

LOCALE_INFO * __cdecl GetShellLocaleInfo(long *param_1,long *param_2)

{
  if (Locale == LOCALE_EASTERN) {
    param_1 = param_2;
  }
  LocaleInfo->ShellFonts = param_1;
  return LocaleInfo;
}
