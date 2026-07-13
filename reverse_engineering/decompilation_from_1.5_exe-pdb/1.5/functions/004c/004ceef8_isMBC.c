/*
 * Entry: 004ceef8
 * Name: isMBC
 * Namespace: Global
 * Signature: long isMBC(char param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl isMBC(char param_1)

{
  if ((((((0x80 < (byte)param_1) && (param_1 != -0x7b)) && (param_1 != -0x7a)) &&
       ((param_1 != -0x15 && (param_1 != -0x14)))) &&
      (((param_1 & 0xf0U) < 0x91 || (0xdf < (param_1 & 0xf0U))))) &&
     (((byte)param_1 < 0xef || (0xf9 < (byte)param_1)))) {
    return 1;
  }
  return 0;
}
