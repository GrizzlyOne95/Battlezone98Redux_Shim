/*
 * Entry: 0047a75b
 * Name: Get_Camera_Owner
 * Namespace: Global
 * Signature: tagENTITY * Get_Camera_Owner(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagENTITY * __cdecl Get_Camera_Owner(void)

{
  if (View_Record.Camera_Owner == (tagENTITY *)0x0) {
    View_Record.Camera_Owner = get_user_entity();
  }
  return View_Record.Camera_Owner;
}
