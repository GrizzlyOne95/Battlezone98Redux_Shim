/*
 * Entry: 00547426
 * Name: DEBUG_monoClearLine
 * Namespace: Global
 * Signature: void DEBUG_monoClearLine(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DEBUG_monoClearLine(void)

{
  uint *puVar1;
  
  puVar1 = (uint *)&DAT_000b0f00;
  do {
    *puVar1 = *puVar1 & 0xff00ff00;
    puVar1 = puVar1 + 1;
  } while ((int)puVar1 < 0xb0fa0);
  return;
}
