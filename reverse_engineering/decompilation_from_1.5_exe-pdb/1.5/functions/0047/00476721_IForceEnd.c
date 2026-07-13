/*
 * Entry: 00476721
 * Name: IForceEnd
 * Namespace: Global
 * Signature: void IForceEnd(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl IForceEnd(void)

{
  FreeLibrary((HMODULE)lib);
  Sleep(200);
  return;
}
