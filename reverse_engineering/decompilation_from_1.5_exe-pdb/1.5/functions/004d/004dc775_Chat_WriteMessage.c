/*
 * Entry: 004dc775
 * Name: Chat_WriteMessage
 * Namespace: Global
 * Signature: void Chat_WriteMessage(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Chat_WriteMessage(char *param_1)

{
  if (chat_display != (void *)0x0) {
    Scroll_AddString(chat_display,param_1);
  }
  return;
}
