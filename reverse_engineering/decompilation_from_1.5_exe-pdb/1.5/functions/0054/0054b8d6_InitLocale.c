/*
 * Entry: 0054b8d6
 * Name: InitLocale
 * Namespace: Global
 * Signature: LOCALE InitLocale(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Enum "LOCALE": Some values do not have unique names */

LOCALE __cdecl InitLocale(void)

{
  LCID LVar1;
  int iVar2;
  ushort *puVar3;
  ushort uVar4;
  char *_Locale;
  undefined1 *local_4e0;
  undefined1 *local_4dc;
  undefined1 *local_4d8;
  undefined1 *local_4d4;
  undefined1 *local_4d0;
  char local_4c8;
  int local_4bc;
  undefined1 local_4b8 [88];
  undefined1 local_460 [172];
  undefined1 local_3b4 [260];
  undefined1 local_2b0 [260];
  undefined1 local_1ac [260];
  undefined1 local_a8 [128];
  char local_28 [32];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_460;
  LVar1 = GetSystemDefaultLCID();
  GetKeyboardType(0);
  local_4bc = GetKeyboardType(1);
  GetKeyboardType(2);
  setlocale(0,"English");
  local_4e0 = local_a8;
  local_4dc = local_1ac;
  local_4d8 = local_2b0;
  local_4d4 = local_4b8;
  local_4d0 = local_3b4;
  iVar2 = dpReadAnetInf(".",&local_4e0);
  if (iVar2 == 0) {
    if (local_4c8 != '\x01') {
      if (local_4c8 == '\x02') goto LAB_0054b988;
      if (local_4c8 == '@') {
LAB_0054b980:
        Locale = LOCALE_EASTERN;
        goto LAB_0054ba12;
      }
      if (local_4c8 != -0x80) {
LAB_0054ba10:
        Locale = LOCALE_UNKNOWN;
        goto LAB_0054ba12;
      }
    }
  }
  else {
    iVar2 = GetPrjFileInfo("Language",local_28,0x20);
    if (iVar2 == 0) {
      uVar4 = (ushort)LVar1 & 0x3ff;
      if (uVar4 != 9) {
        if (uVar4 != 7) {
          if (uVar4 != 0x11) goto LAB_0054ba10;
          goto LAB_0054b980;
        }
        goto LAB_0054b988;
      }
    }
    else {
      iVar2 = _stricmp(local_28,"english");
      if (iVar2 != 0) {
        iVar2 = _stricmp(local_28,"german");
        if (iVar2 != 0) {
          iVar2 = _stricmp(local_28,"japanese");
          Locale = (-(uint)(iVar2 != 0) & 0xfffffffd) + LOCALE_EASTERN;
          goto LAB_0054ba12;
        }
LAB_0054b988:
        Locale = LOCALE_GERMAN;
        goto LAB_0054ba12;
      }
    }
  }
  Locale = LOCALE_ENGLISH;
LAB_0054ba12:
  if (Locale == LOCALE_EASTERN) {
    iVar2 = GetPrjFileInfo("Keyboard",local_28,0x20);
    if ((iVar2 != 0) && (iVar2 = _stricmp(local_28,"NEC"), iVar2 == 0)) {
      local_4bc = 0xd01;
    }
    LocaleInfo = &LocaleInfo_Eastern;
    if (local_4bc == 0xd01) {
      LocaleInfo_Eastern.KeyNames = (char **)&jn_discreteNames;
      LocaleInfo_Eastern.KeyDescriptions = (char **)&jn_discreteDescriptions;
    }
    else {
      LocaleInfo_Eastern.KeyDescriptions = (char **)&j1_discreteDescriptions;
      if (local_4bc != 0xd05) {
        LocaleInfo_Eastern.KeyDescriptions = (char **)&e_discreteDescriptions;
      }
    }
    setlocale(0,"Japanese");
    puVar3 = SetupRemapTable();
    LocaleInfo->RemapTablePtr = puVar3;
  }
  else {
    LocaleInfo = &LocaleInfo_Western;
    if (Locale == LOCALE_GERMAN) {
      LocaleInfo_Western.KeyDescriptions = (char **)&g_discreteDescriptions;
      _Locale = "German";
    }
    else {
      LocaleInfo_Western.KeyDescriptions = (char **)&e_discreteDescriptions;
      _Locale = "English";
    }
    setlocale(0,_Locale);
  }
  RemapTablePtr = LocaleInfo->RemapTablePtr;
  isMBCS = LocaleInfo->isMBCS;
  LocaleInfo->Locale = Locale;
  return Locale;
}
