/*
 * Entry: 0056ea7b
 * Name: init_screen_pos
 * Namespace: Global
 * Signature: void init_screen_pos(HWND__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl init_screen_pos(HWND__ *param_1)

{
  HWND hWnd;
  tagPOINT *lpPoint;
  tagRECT local_1c;
  tagPOINT local_c;
  
  GetClientRect((HWND)shell_hwnd,&local_1c);
  local_c.x = local_1c.left;
  local_c.y = local_1c.top;
  lpPoint = &local_c;
  hWnd = GetWindow((HWND)param_1,4);
  ClientToScreen(hWnd,lpPoint);
  local_1c.left = local_1c.left + local_c.x;
  local_1c.top = local_1c.top + local_c.y;
  local_1c.right = local_1c.right + local_c.x;
  local_1c.bottom = local_1c.bottom + local_c.y;
  MoveWindow((HWND)param_1,local_1c.left,local_1c.top,local_1c.right - local_1c.left,
             local_1c.bottom - local_1c.top,1);
  return;
}
