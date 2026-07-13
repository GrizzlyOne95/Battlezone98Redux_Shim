/*
 * Entry: 004f39c1
 * Name: GetCharacterAddress
 * Namespace: Global
 * Signature: CHARACTER * GetCharacterAddress(FONT * param_1, ushort param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CHARACTER * __cdecl GetCharacterAddress(FONT *param_1,ushort param_2)

{
  ushort uVar1;
  uint uVar2;
  
  if ((param_1->type & 0x100U) == 0) {
    uVar2 = param_2 & 0xff;
    if (param_1->char_count <= (int)uVar2) {
      uVar2 = 0x2a;
    }
    return *(CHARACTER **)((int)(param_1[1].Back_Foreground + -1) + 0xf4 + uVar2 * 4);
  }
  if (RemapTablePtr[param_2 & 0xffff00ff] == 0) {
    uVar1 = param_2 & 0xff;
  }
  else {
    uVar1 = RemapTablePtr[param_2 & 0xffff00ff] + (param_2 >> 8);
  }
  return *(CHARACTER **)((int)(param_1[1].Back_Foreground + -1) + 0xf4 + (uint)uVar1 * 4);
}
