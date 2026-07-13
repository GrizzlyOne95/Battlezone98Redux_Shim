/*
 * Entry: 0054d5d0
 * Name: Mono_PageUp
 * Namespace: Global
 * Signature: void Mono_PageUp(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mono_PageUp(void)

{
  if (active_screen != 0) {
    start_line = start_line + -10;
    if (start_line < 0) {
      start_line = 0;
    }
    Mono_SetActive((long)(screens + screen_index));
  }
  return;
}
