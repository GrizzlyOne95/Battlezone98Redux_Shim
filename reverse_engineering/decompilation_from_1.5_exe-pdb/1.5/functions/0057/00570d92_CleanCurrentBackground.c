/*
 * Entry: 00570d92
 * Name: CleanCurrentBackground
 * Namespace: Global
 * Signature: void CleanCurrentBackground(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CleanCurrentBackground(void)

{
  if (hCurrentBackground != (HBITMAP__ *)0x0) {
    DeleteObject(hCurrentBackground);
  }
  hCurrentBackground = (HBITMAP__ *)0x0;
  return;
}
