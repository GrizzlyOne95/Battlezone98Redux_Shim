/*
 * Entry: 005046da
 * Name: set_hardware_mode
 * Namespace: Global
 * Signature: int set_hardware_mode(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl set_hardware_mode(int param_1)

{
  if (param_1 != (uint)SessionFlags.oldMode) {
    SessionFlags.newMode = (uchar)param_1;
    SessionFlags.newRes = (UserProfilePtr->graphicDetail).resolution;
    (UserProfilePtr->graphicDetail).hardware = SessionFlags.oldMode;
    (UserProfilePtr->graphicDetail).resolution = SessionFlags.oldRes;
    SessionFlags.newHWSW = ((param_1 == 0) - 1U & 0xe1) + 0xf;
  }
  return 1;
}
