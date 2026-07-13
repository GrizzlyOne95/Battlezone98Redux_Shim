/*
 * Entry: 00582234
 * Name: TextInput_AdjustScrollPosLeft
 * Namespace: Global
 * Signature: void TextInput_AdjustScrollPosLeft(INPUT_REGION * param_1, ulong param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl TextInput_AdjustScrollPosLeft(INPUT_REGION *param_1,ulong param_2)

{
  uint in_ECX;
  int in_EDX;
  
  if (in_ECX < *(uint *)(in_EDX + 0x114)) {
    *(undefined4 *)(in_EDX + 0x118) = 0;
    *(uint *)(in_EDX + 0x114) = in_ECX;
  }
  return;
}
