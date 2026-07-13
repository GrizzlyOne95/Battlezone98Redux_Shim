/*
 * Entry: 004f8726
 * Name: Get_TOD_Angle
 * Namespace: Global
 * Signature: float Get_TOD_Angle(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Get_TOD_Angle(void)

{
  return TOD_tbl[Lights_Struct.TOD_entry].Angle;
}
