/*
 * Entry: 004dc798
 * Name: Chat_Show
 * Namespace: Global
 * Signature: void Chat_Show(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Chat_Show(int param_1)

{
  Scroll_ShowRegion(chat_display,param_1);
  chat_show = param_1;
  return;
}
