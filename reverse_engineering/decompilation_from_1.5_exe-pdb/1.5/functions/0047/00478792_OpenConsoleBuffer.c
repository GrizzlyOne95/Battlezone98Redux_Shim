/*
 * Entry: 00478792
 * Name: OpenConsoleBuffer
 * Namespace: Global
 * Signature: void OpenConsoleBuffer(void * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl OpenConsoleBuffer(void *param_1,char *param_2)

{
  if (console_level < 1) {
    ShowWindow((HWND)console_hwnd,4);
  }
  console_level = console_level + 1;
  console_stack_buffer[console_level] = param_1;
  SetConsoleActiveScreenBuffer(param_1);
  console_stack_title[console_level] = param_2;
  SetConsoleTitleA(param_2);
  return;
}
