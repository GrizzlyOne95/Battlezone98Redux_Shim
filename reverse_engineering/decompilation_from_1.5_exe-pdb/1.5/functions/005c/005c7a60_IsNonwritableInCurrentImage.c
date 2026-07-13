/*
 * Entry: 005c7a60
 * Name: _IsNonwritableInCurrentImage
 * Namespace: Global
 * Signature: int _IsNonwritableInCurrentImage(uchar * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl _IsNonwritableInCurrentImage(uchar *param_1)

{
  int iVar1;
  _IMAGE_SECTION_HEADER *p_Var2;
  void *local_14;
  code *pcStack_10;
  uint local_c;
  undefined4 local_8;
  
  pcStack_10 = _except_handler4;
  local_14 = ExceptionList;
  local_c = __security_cookie ^ 0x623898;
  ExceptionList = &local_14;
  local_8 = 0;
  iVar1 = _ValidateImageBase((uchar *)&IMAGE_DOS_HEADER_00400000);
  if (iVar1 != 0) {
    p_Var2 = _FindPESection((uchar *)&IMAGE_DOS_HEADER_00400000,(ulong)(param_1 + -0x400000));
    if (p_Var2 != (_IMAGE_SECTION_HEADER *)0x0) {
      ExceptionList = local_14;
      return ~(p_Var2->Characteristics >> 0x1f) & 1;
    }
  }
  ExceptionList = local_14;
  return 0;
}
