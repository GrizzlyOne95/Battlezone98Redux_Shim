/*
 * Entry: 00571075
 * Name: set_cursor
 * Namespace: Global
 * Signature: void set_cursor(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl set_cursor(int param_1)

{
  if ((((param_1 != 0) && (thisCursor = gameCursor, param_1 != 1)) &&
      (thisCursor = waitCursor, param_1 != 2)) && (thisCursor = gameCursor, param_1 == 3)) {
    thisCursor = editCursor;
  }
  oldCursor = (HICON__ *)SetCursor((HCURSOR)thisCursor);
  return;
}
