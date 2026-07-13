/*
 * Entry: 004f4487
 * Name: OpenFont
 * Namespace: Global
 * Signature: HFONT__ * OpenFont(char * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

HFONT__ * __cdecl OpenFont(char *param_1,long param_2)

{
  char cVar1;
  int iVar2;
  HDC hdc;
  HFONT pHVar3;
  DWORD flags;
  LOGFONTA local_44;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_44.lfHeight = param_2;
  local_44.lfWidth = 0;
  local_44.lfEscapement = 0;
  local_44.lfOrientation = 0;
  local_44.lfWeight = 100;
  local_44.lfItalic = '\0';
  local_44.lfUnderline = '\0';
  local_44.lfStrikeOut = '\0';
  local_44.lfCharSet = '\0';
  local_44.lfOutPrecision = '\x04';
  local_44.lfClipPrecision = '\0';
  local_44.lfQuality = '\x02';
  local_44.lfPitchAndFamily = '\0';
  iVar2 = 0x1c - (int)param_1;
  do {
    cVar1 = *param_1;
    param_1[(int)&local_44 + iVar2] = cVar1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  iVar2 = IsJapanese();
  if (iVar2 != 0) {
    local_44.lfCharSet = 0x80;
  }
  flags = 1;
  hdc = (*Device.VideoMode.GetVideoDC)(&Device);
  SetMapperFlags(hdc,flags);
  pHVar3 = CreateFontIndirectA(&local_44);
  (*Device.VideoMode.ReleaseVideoDC)(&Device);
  return (HFONT__ *)pHVar3;
}
