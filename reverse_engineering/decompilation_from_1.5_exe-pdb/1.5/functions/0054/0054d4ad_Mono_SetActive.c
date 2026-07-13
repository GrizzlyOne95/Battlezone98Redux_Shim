/*
 * Entry: 0054d4ad
 * Name: Mono_SetActive
 * Namespace: Global
 * Signature: void Mono_SetActive(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mono_SetActive(long param_1)

{
  SMALL_RECT local_c;
  
  active_screen = param_1;
  if (param_1 != 0) {
    AllocConsoleIfNeeded();
    if (console_out == (void *)0xffffffff) {
      local_c.Left = 0;
      local_c.Top = 0;
      local_c.Right = 0x4f;
      local_c.Bottom = 0x18;
      console_out = CreateConsoleScreenBuffer(0xc0000000,3,(SECURITY_ATTRIBUTES *)0x0,1,(LPVOID)0x0)
      ;
      SetConsoleScreenBufferSize(console_out,(COORD)(_COORD)0x190050);
      SetConsoleWindowInfo(console_out,1,&local_c);
      OpenConsoleBuffer(console_out,"Mono Debug");
    }
    (**(code **)active_screen)();
    return;
  }
  Mono_Clear(0);
  CloseConsoleBuffer(console_out);
  return;
}
