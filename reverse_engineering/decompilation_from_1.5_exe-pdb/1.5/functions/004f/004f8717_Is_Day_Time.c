/*
 * Entry: 004f8717
 * Name: Is_Day_Time
 * Namespace: Global
 * Signature: int Is_Day_Time(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Is_Day_Time(void)

{
  return TOD_tbl[Lights_Struct.TOD_entry].Day_Time;
}
