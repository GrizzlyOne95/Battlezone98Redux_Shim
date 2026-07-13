/*
 * Entry: 004dc7b3
 * Name: Chat_Toggle
 * Namespace: Global
 * Signature: void Chat_Toggle(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Chat_Toggle(void)

{
  chat_show = (int)(chat_show == 0);
  Chat_Show(chat_show);
  return;
}
