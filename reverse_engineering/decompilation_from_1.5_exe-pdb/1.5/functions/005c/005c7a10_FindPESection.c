/*
 * Entry: 005c7a10
 * Name: _FindPESection
 * Namespace: Global
 * Signature: _IMAGE_SECTION_HEADER * _FindPESection(uchar * param_1, ulong param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_IMAGE_SECTION_HEADER * __cdecl _FindPESection(uchar *param_1,ulong param_2)

{
  int iVar1;
  _IMAGE_SECTION_HEADER *p_Var2;
  uint uVar3;
  
  iVar1 = *(int *)(param_1 + 0x3c);
  uVar3 = 0;
  p_Var2 = (_IMAGE_SECTION_HEADER *)(param_1 + *(ushort *)(param_1 + iVar1 + 0x14) + 0x18 + iVar1);
  if (*(ushort *)(param_1 + iVar1 + 6) != 0) {
    do {
      if ((p_Var2->VirtualAddress <= param_2) &&
         (param_2 < (p_Var2->Misc).PhysicalAddress + p_Var2->VirtualAddress)) {
        return p_Var2;
      }
      uVar3 = uVar3 + 1;
      p_Var2 = p_Var2 + 1;
    } while (uVar3 < *(ushort *)(param_1 + iVar1 + 6));
  }
  return (_IMAGE_SECTION_HEADER *)0x0;
}
