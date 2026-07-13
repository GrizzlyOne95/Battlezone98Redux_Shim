/*
 * Entry: 0054bb5f
 * Name: LocaleNetworkFont
 * Namespace: Global
 * Signature: MILES_FONT_INFO * LocaleNetworkFont(NETWORK_FONT_INDEX param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Enum "LOCALE": Some values do not have unique names */

MILES_FONT_INFO * __cdecl LocaleNetworkFont(NETWORK_FONT_INDEX param_1,char *param_2)

{
  if ((LocaleInfo != (LOCALE_INFO *)0x0) && ((int)param_1 < 4)) {
    return LocaleInfo->SimFontsNetwork + param_1;
  }
  NetworkFontDefault[0].name = param_2;
  return NetworkFontDefault;
}
