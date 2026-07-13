/*
 * Entry: 0054d5fd
 * Name: Mono_PageDown
 * Namespace: Global
 * Signature: void Mono_PageDown(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mono_PageDown(void)

{
  if (active_screen != 0) {
    start_line = start_line + 10;
    Mono_SetActive((long)(screens + screen_index));
  }
  return;
}
