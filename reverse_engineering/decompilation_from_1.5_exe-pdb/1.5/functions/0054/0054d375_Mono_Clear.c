/*
 * Entry: 0054d375
 * Name: Mono_Clear
 * Namespace: Global
 * Signature: void Mono_Clear(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mono_Clear(long param_1)

{
  if (param_1 == active_screen) {
    FillConsoleOutputCharacterA(console_out,'\0',2000,(COORD)0x0,(LPDWORD)&param_1);
  }
  return;
}
