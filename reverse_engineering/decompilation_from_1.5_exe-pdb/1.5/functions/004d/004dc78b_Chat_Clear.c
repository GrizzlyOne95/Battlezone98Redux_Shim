/*
 * Entry: 004dc78b
 * Name: Chat_Clear
 * Namespace: Global
 * Signature: void Chat_Clear(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Chat_Clear(void)

{
  Scroll_ClearRegion(chat_display);
  return;
}
