/*
 * Entry: 0054bb41
 * Name: LocaleNotepadFont
 * Namespace: Global
 * Signature: RDFONT * LocaleNotepadFont(NOTEPAD_FONT_INDEX param_1, RDFONT * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Enum "LOCALE": Some values do not have unique names */

RDFONT * __cdecl LocaleNotepadFont(NOTEPAD_FONT_INDEX param_1,RDFONT *param_2)

{
  if ((LocaleInfo != (LOCALE_INFO *)0x0) && ((int)param_1 < 2)) {
    return LocaleInfo->SimRDFontsNotepad[param_1];
  }
  return param_2;
}
