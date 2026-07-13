/*
 * Entry: 0047816c
 * Name: Get_Current_Camera
 * Namespace: Global
 * Signature: CAMERA * Get_Current_Camera(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CAMERA * __cdecl Get_Current_Camera(void)

{
  return &View_Record.MainCam;
}
