/*
 * Entry: 005711e1
 * Name: EnumButtonFontsProc
 * Namespace: Global
 * Signature: int EnumButtonFontsProc(tagLOGFONTA * param_1, tagTEXTMETRICA * param_2, ulong param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl
EnumButtonFontsProc(tagLOGFONTA *param_1,tagTEXTMETRICA *param_2,ulong param_3,long param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  long extraout_EAX;
  char *_Str1;
  LOGFONTA local_44;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_4 == 0) {
LAB_005712cb:
    hButtonFont = (HFONT__ *)CreateFontIndirectA((LOGFONTA *)param_1);
    local_44.lfHeight = param_1->lfHeight;
LAB_005712d9:
    iVar3 = 0;
    nButtonFontSize = local_44.lfHeight;
  }
  else {
    if (param_4 == 1) {
      iVar3 = _stricmp(param_1->lfFaceName,"System");
      if (iVar3 == 0) goto LAB_005712cb;
    }
    else if (param_4 == 2) {
      _Str1 = param_1->lfFaceName;
      iVar3 = _stricmp(_Str1,desiredFont);
      if (iVar3 == 0) {
        iVar3 = GetScreenDPI();
        if (iVar3 == 0x60) {
          param_1->lfHeight = nDesiredHeight;
          _ftol2_sse();
          param_1->lfWidth = extraout_EAX;
          hButtonFont = (HFONT__ *)CreateFontIndirectA((LOGFONTA *)param_1);
          local_44.lfHeight = param_1->lfHeight;
        }
        else {
          memset(&local_44,0,0x3c);
          iVar2 = 0x1c - (int)_Str1;
          do {
            cVar1 = *_Str1;
            _Str1[(int)&local_44 + iVar2] = cVar1;
            _Str1 = _Str1 + 1;
          } while (cVar1 != '\0');
          local_44.lfHeight = MulDiv(nDesiredHeight,0x60,iVar3);
          local_44.lfHeight = -local_44.lfHeight;
          hButtonFont = (HFONT__ *)CreateFontIndirectA(&local_44);
        }
        goto LAB_005712d9;
      }
    }
    nButtonFontSize = -1;
    iVar3 = 1;
  }
  return iVar3;
}
