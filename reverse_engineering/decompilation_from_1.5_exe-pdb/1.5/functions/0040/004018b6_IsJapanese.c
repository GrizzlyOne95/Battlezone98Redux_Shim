/*
 * Entry: 004018b6
 * Name: IsJapanese
 * Namespace: Global
 * Signature: int IsJapanese(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Enum "LOCALE": Some values do not have unique names */

int __cdecl IsJapanese(void)

{
  if (LocaleInfo != (LOCALE_INFO *)0x0) {
    return (uint)(LocaleInfo->Locale == LOCALE_EASTERN);
  }
  return 0;
}
