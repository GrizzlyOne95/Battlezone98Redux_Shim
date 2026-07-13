/*
 * Entry: 004787e0
 * Name: CloseConsoleBuffer
 * Namespace: Global
 * Signature: int CloseConsoleBuffer(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CloseConsoleBuffer(void *param_1)

{
  int iVar1;
  
  if (console_level < 0) {
    return 0;
  }
  if (console_stack_buffer[console_level] != param_1) {
    iVar1 = console_level + -1;
    while( true ) {
      if (iVar1 < 0) {
        return 0;
      }
      if (console_stack_buffer[iVar1] == param_1) break;
      iVar1 = iVar1 + 1;
    }
    memmove(console_stack_buffer + iVar1,console_stack_buffer + iVar1 + 1,
            (console_level - iVar1) * 4);
    memmove(console_stack_title + iVar1,console_stack_title + iVar1 + 1,(console_level - iVar1) * 4)
    ;
    console_level = console_level + -1;
    return 1;
  }
  if (console_level < 1) {
    ShowWindow((HWND)console_hwnd,0);
  }
  else {
    iVar1 = console_level + 3;
    console_level = console_level + -1;
    SetConsoleActiveScreenBuffer(console_stack_title[iVar1]);
    SetConsoleTitleA(console_stack_title[console_level]);
  }
  return 1;
}
