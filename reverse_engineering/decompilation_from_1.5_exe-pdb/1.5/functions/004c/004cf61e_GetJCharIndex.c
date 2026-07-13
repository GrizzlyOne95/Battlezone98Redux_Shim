/*
 * Entry: 004cf61e
 * Name: GetJCharIndex
 * Namespace: Global
 * Signature: int GetJCharIndex(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetJCharIndex(ushort param_1)

{
  ushort uVar1;
  
  if (RemapTablePtr[param_1 & 0xffff00ff] == 0) {
    uVar1 = param_1 & 0xff;
  }
  else {
    uVar1 = RemapTablePtr[param_1 & 0xffff00ff] + (param_1 >> 8);
  }
  return (uint)uVar1;
}
