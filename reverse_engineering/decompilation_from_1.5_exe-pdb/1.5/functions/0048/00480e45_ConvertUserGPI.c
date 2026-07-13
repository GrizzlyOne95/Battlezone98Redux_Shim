/*
 * Entry: 00480e45
 * Name: ConvertUserGPI
 * Namespace: Global
 * Signature: void ConvertUserGPI(GAS_PREP_INFO * param_1, GAS_PREP_INFO * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ConvertUserGPI(GAS_PREP_INFO *param_1,GAS_PREP_INFO *param_2)

{
  int in_EAX;
  int in_ECX;
  
  if ((in_ECX != 0) && (in_EAX != 0)) {
    if (*(int *)(in_EAX + 4) == -1) {
      *(undefined4 *)(in_EAX + 4) = 0x32;
    }
    if ((in_ECX != in_EAX) && (*(int *)(in_ECX + 4) != -1)) {
      *(int *)(in_EAX + 4) = *(int *)(in_EAX + 4) + *(int *)(in_ECX + 4);
    }
    if (*(int *)(in_ECX + 8) == -1) {
      if (*(int *)(in_EAX + 8) == -1) {
        *(undefined4 *)(in_EAX + 8) = 4;
      }
    }
    else {
      *(int *)(in_EAX + 8) = *(int *)(in_ECX + 8);
    }
    if (*(int *)(in_ECX + 0xc) == -1) {
      if (*(int *)(in_EAX + 0xc) == -1) {
        *(undefined4 *)(in_EAX + 0xc) = 0;
      }
    }
    else {
      *(int *)(in_EAX + 0xc) = *(int *)(in_ECX + 0xc);
    }
    if (*(int *)(in_ECX + 0x14) == -1) {
      if (*(int *)(in_EAX + 0x14) == -1) {
        *(undefined4 *)(in_EAX + 0x14) = 0;
      }
    }
    else {
      *(int *)(in_EAX + 0x14) = *(int *)(in_ECX + 0x14);
    }
    if (*(int *)(in_ECX + 0x10) != -1) {
      *(int *)(in_EAX + 0x10) = *(int *)(in_ECX + 0x10);
      return;
    }
    if (*(int *)(in_EAX + 0x10) == -1) {
      *(undefined4 *)(in_EAX + 0x10) = 100;
    }
  }
  return;
}
