/*
 * Entry: 0056e9b3
 * Name: GetLangIni
 * Namespace: Global
 * Signature: void GetLangIni(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GetLangIni(void)

{
  int iVar1;
  
  if (first != 0) {
    first = 0;
    iVar1 = IsJapanese();
    if (iVar1 != 0) {
      GetINIString("Config","ShellFont",s__l_r__o_S_V_b_N,defaultFont,0x40,"lang.ini");
      defaultFontSize1 = GetINIInt("Config","ShellFontSize1",0xe,"lang.ini");
      defaultFontSize2 = GetINIInt("Config","ShellFontSize2",0xc,"lang.ini");
    }
  }
  return;
}
