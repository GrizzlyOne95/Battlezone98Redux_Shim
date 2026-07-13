/*
 * Entry: 004bd8e5
 * Name: giddi_close
 * Namespace: Global
 * Signature: int giddi_close(_GIDDI_DEVDESC * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl giddi_close(_GIDDI_DEVDESC *param_1)

{
  int iVar1;
  
  ClipCursor((RECT *)0x0);
  clipMouse = 0;
  do {
    iVar1 = ShowCursor(1);
  } while (iVar1 < PrevCursorSemaphoreValue);
  return 0;
}
