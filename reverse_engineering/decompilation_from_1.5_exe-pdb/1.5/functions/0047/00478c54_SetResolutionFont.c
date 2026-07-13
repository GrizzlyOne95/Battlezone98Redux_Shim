/*
 * Entry: 00478c54
 * Name: SetResolutionFont
 * Namespace: Global
 * Signature: void SetResolutionFont(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetResolutionFont(void)

{
  int iVar1;
  
  Default_Font = Font_Read(&fontInfo);
  iVar1 = IsJapanese();
  if (iVar1 != 0) {
    J_Font = Font_Read(&jFontInfo);
  }
  return;
}
