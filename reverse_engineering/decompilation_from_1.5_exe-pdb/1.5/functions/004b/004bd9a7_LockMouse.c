/*
 * Entry: 004bd9a7
 * Name: LockMouse
 * Namespace: Global
 * Signature: void LockMouse(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl LockMouse(void)

{
  HWND pHVar1;
  uint uVar2;
  tagPOINT local_c;
  
  GetWindowScreenCoordinates(&ourWindowRect,Device.Client_Width,Device.Client_Height);
  ClipCursor((RECT *)&ourWindowRect);
  mouseData.analog_x = 0;
  mouseData.analog_dx = 0;
  mouseData.analog_y = 0;
  mouseData.analog_dy = 0;
  discreteSetMap = 0;
  discreteClrMap = 0;
  clipMouse = 1;
  pHVar1 = GetFocus();
  if (pHVar1 == (HWND)Device.hwndApp) {
    local_c.x = Device.Client_Width / 2;
    local_c.y = Device.Client_Height / 2;
    ClientToScreen((HWND)Device.hwndApp,&local_c);
    SetCursorPos(local_c.x,local_c.y);
  }
  do {
    uVar2 = ShowCursor(0);
  } while (uVar2 < 0x80000000);
  return;
}
