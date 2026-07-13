/*
 * Entry: 0054d59f
 * Name: Mono_Next
 * Namespace: Global
 * Signature: void Mono_Next(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mono_Next(void)

{
  if ((active_screen != 0) && (next_empty_screen != 0)) {
    screen_index = (screen_index + 1) % next_empty_screen;
    Mono_SetActive((long)(screens + screen_index));
  }
  return;
}
