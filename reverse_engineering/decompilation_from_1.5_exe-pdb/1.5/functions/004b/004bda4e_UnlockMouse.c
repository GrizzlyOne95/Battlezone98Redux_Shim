/*
 * Entry: 004bda4e
 * Name: UnlockMouse
 * Namespace: Global
 * Signature: void UnlockMouse(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UnlockMouse(void)

{
  HWND pHVar1;
  int iVar2;
  tagPOINT local_c;
  
  ClipCursor((RECT *)0x0);
  clipMouse = 0;
  mouseData.analog_x = 0;
  mouseData.analog_dx = 0;
  mouseData.analog_y = 0;
  mouseData.analog_dy = 0;
  pHVar1 = GetFocus();
  if (pHVar1 == (HWND)Device.hwndApp) {
    local_c.x = Device.Client_Width / 2;
    local_c.y = Device.Client_Height / 2;
    ClientToScreen((HWND)Device.hwndApp,&local_c);
    SetCursorPos(local_c.x,local_c.y);
  }
  do {
    iVar2 = ShowCursor(1);
  } while (iVar2 < 0);
  return;
}
