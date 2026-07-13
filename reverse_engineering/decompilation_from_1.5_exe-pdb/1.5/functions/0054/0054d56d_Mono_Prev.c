/*
 * Entry: 0054d56d
 * Name: Mono_Prev
 * Namespace: Global
 * Signature: void Mono_Prev(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mono_Prev(void)

{
  if ((active_screen != 0) && (next_empty_screen != 0)) {
    screen_index = screen_index + -1;
    if (screen_index < 0) {
      screen_index = next_empty_screen + -1;
    }
    Mono_SetActive((long)(screens + screen_index));
  }
  return;
}
