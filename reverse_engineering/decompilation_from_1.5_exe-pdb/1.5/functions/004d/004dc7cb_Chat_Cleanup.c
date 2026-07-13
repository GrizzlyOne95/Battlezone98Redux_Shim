/*
 * Entry: 004dc7cb
 * Name: Chat_Cleanup
 * Namespace: Global
 * Signature: void Chat_Cleanup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Chat_Cleanup(void)

{
  Scroll_DestroyRegion(chat_display);
  TextInput_DestroyRegion(chat_entry);
  chat_display = (void *)0x0;
  chat_entry = (void *)0x0;
  return;
}
