/*
 * Entry: 00480ddd
 * Name: ConvertFileGPI
 * Namespace: Global
 * Signature: void ConvertFileGPI(GAS_PREP_INFO * param_1, GAS_PREP_INFO * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ConvertFileGPI(GAS_PREP_INFO *param_1,GAS_PREP_INFO *param_2)

{
  undefined4 *in_EAX;
  undefined4 *in_ECX;
  
  if ((in_ECX != (undefined4 *)0x0) || (in_EAX != (undefined4 *)0x0)) {
    *in_ECX = *in_EAX;
    if (in_EAX[1] == -1) {
      in_ECX[1] = 0x32;
    }
    else {
      in_ECX[1] = in_EAX[1];
    }
    if (in_EAX[2] == -1) {
      in_ECX[2] = 4;
    }
    else {
      in_ECX[2] = in_EAX[2];
    }
    in_ECX[3] = -(uint)(in_EAX[3] != 0xffffffff) & in_EAX[3];
    in_ECX[5] = -(uint)(in_EAX[5] != 0xffffffff) & in_EAX[5];
    if (in_EAX[4] == -1) {
      in_ECX[4] = 100;
      return;
    }
    in_ECX[4] = in_EAX[4];
  }
  return;
}
