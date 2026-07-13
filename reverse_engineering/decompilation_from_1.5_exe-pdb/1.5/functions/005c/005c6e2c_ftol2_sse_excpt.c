/*
 * Entry: 005c6e2c
 * Name: _ftol2_sse_excpt
 * Namespace: Global
 * Signature: void _ftol2_sse_excpt(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _ftol2_sse_excpt(void)

{
  ushort in_FPUControlWord;
  
  if ((__sse2_available != 0) && ((in_FPUControlWord & 0x7f) == 0x7f)) {
    return;
  }
  return;
}
