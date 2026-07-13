/*
 * Entry: 0058529f
 * Name: len_of_coded_match
 * Namespace: Global
 * Signature: ulong len_of_coded_match(ulong param_1, ulong param_2, ulong param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __cdecl len_of_coded_match(ulong param_1,ulong param_2,ulong param_3)

{
  uint in_EAX;
  uint in_EDX;
  uint uVar1;
  uint unaff_EDI;
  
  if (1 < in_EDX) {
    if (in_EDX != 2) {
      if ((in_EDX < 0xf) && (unaff_EDI < 0x401)) {
        return 2;
      }
      if (((in_EDX == 3) && (unaff_EDI < 0x801)) && (3 < in_EAX)) {
        return 2;
      }
      if (unaff_EDI < 0x4001) {
        if (in_EDX < 0x22) {
          return 3;
        }
        uVar1 = in_EDX - 0x21;
      }
      else {
        if (0xbfff < unaff_EDI) {
          return 0;
        }
        if (in_EDX < 10) {
          return 3;
        }
        uVar1 = in_EDX - 9;
      }
      if (0xff < uVar1) {
        return (uVar1 - 0x100) / 0xff + 5;
      }
      return 4;
    }
    if ((unaff_EDI < 0x401) && (in_EAX - 1 < 3)) {
      return 2;
    }
  }
  return 0;
}
