
CMFCFontInfo * __thiscall FUN_0071de30(CMFCFontInfo *param_1,uint param_2)

{
  CMFCFontInfo::~CMFCFontInfo(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

