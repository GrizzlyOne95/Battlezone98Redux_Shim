/*
 * Entry: 004f8744
 * Name: Get_Ambient_Attenuation
 * Namespace: Global
 * Signature: float Get_Ambient_Attenuation(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Get_Ambient_Attenuation(void)

{
  return TOD_tbl[Lights_Struct.TOD_entry].Att;
}
