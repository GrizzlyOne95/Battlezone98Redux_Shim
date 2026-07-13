/*
 * Entry: 004bd1ea
 * Name: IsGerman
 * Namespace: Global
 * Signature: int IsGerman(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Enum "LOCALE": Some values do not have unique names */

int __cdecl IsGerman(void)

{
  if (LocaleInfo != (LOCALE_INFO *)0x0) {
    return (uint)(LocaleInfo->Locale == LOCALE_GERMAN);
  }
  return 0;
}
