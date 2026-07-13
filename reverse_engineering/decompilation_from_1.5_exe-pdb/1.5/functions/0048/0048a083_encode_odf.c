/*
 * Entry: 0048a083
 * Name: encode_odf
 * Namespace: Global
 * Signature: uchar encode_odf(long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl encode_odf(long64 param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  while (((int)(param_1 & 0x7f7f7f7f7f7f7f7fU) != (int)codes[uVar1] ||
         ((int)((param_1 & 0x7f7f7f7f7f7f7f7fU) >> 0x20) != *(int *)((int)codes + uVar1 * 8 + 4))))
  {
    uVar1 = uVar1 + 1;
    if (0x65 < uVar1) {
      return '\0';
    }
  }
  return (char)uVar1 + 0x80;
}
