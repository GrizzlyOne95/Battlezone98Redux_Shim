/*
 * Entry: 004bd907
 * Name: giddi_reset
 * Namespace: Global
 * Signature: int giddi_reset(MOUSE_DATA * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl giddi_reset(MOUSE_DATA *param_1,int param_2)

{
  if (param_2 == 0) {
    param_1->analog_x = 0;
  }
  else if (param_2 == 1) {
    param_1->analog_dx = 0;
  }
  else if (param_2 == 2) {
    param_1->analog_y = 0;
  }
  else if (param_2 == 3) {
    param_1->analog_dy = 0;
  }
  return 0;
}
