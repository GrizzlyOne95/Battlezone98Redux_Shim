/*
 * Entry: 004f8735
 * Name: Get_Ambient
 * Namespace: Global
 * Signature: float Get_Ambient(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Get_Ambient(void)

{
  return TOD_tbl[Lights_Struct.TOD_entry].Ambient;
}
