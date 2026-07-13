/*
 * Entry: 0054bb23
 * Name: LocaleMenuFont
 * Namespace: Global
 * Signature: RDFONT * LocaleMenuFont(MENU_FONT_INDEX param_1, RDFONT * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Enum "LOCALE": Some values do not have unique names */

RDFONT * __cdecl LocaleMenuFont(MENU_FONT_INDEX param_1,RDFONT *param_2)

{
  if ((LocaleInfo != (LOCALE_INFO *)0x0) && ((int)param_1 < 8)) {
    return LocaleInfo->SimRDFontsMenu[param_1];
  }
  return param_2;
}
