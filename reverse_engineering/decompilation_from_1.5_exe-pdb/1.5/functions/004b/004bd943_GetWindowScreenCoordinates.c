/*
 * Entry: 004bd943
 * Name: GetWindowScreenCoordinates
 * Namespace: Global
 * Signature: void GetWindowScreenCoordinates(tagRECT * param_1, long param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GetWindowScreenCoordinates(tagRECT *param_1,long param_2,long param_3)

{
  tagPOINT local_c;
  
  local_c.y = 0;
  local_c.x = 0;
  ClientToScreen((HWND)Device.hwndApp,&local_c);
  param_1->left = local_c.x;
  param_1->top = local_c.y;
  local_c.x = param_2 + -1;
  local_c.y = param_3 + -1;
  ClientToScreen((HWND)Device.hwndApp,&local_c);
  param_1->right = local_c.x;
  param_1->bottom = local_c.y;
  return;
}
