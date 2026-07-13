/*
 * Entry: 004bd3fe
 * Name: check_extended_codes
 * Namespace: Global
 * Signature: int check_extended_codes(int param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl check_extended_codes(int param_1,long param_2)

{
  if (((param_1 != 0) && (((uint)param_2 >> 0x10 & 0x100) != 0)) && (param_1 < 0x59)) {
    param_1 = ExtendedCodes[param_1];
  }
  return param_1;
}
