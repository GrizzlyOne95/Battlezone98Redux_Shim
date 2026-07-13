/*
 * Entry: 004f9476
 * Name: Draw_Translucent2_Line
 * Namespace: Global
 * Signature: void Draw_Translucent2_Line(uchar * param_1, long param_2, long param_3, long param_4, long param_5, long param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Draw_Translucent2_Line
          (uchar *param_1,long param_2,long param_3,long param_4,long param_5,long param_6)

{
  int in_EAX;
  int iVar1;
  int in_ECX;
  int iVar2;
  int in_EDX;
  int local_14 [4];
  
  if (param_2 < in_EAX) {
    iVar1 = param_2 * 2 - in_EAX;
    local_14[2] = iVar1 - in_EAX;
    local_14[0] = in_EDX + in_ECX;
    local_14[3] = param_2 * 2;
    iVar2 = in_EAX + 1;
  }
  else {
    iVar1 = in_EAX * 2 - param_2;
    local_14[0] = in_ECX + in_EDX;
    local_14[2] = iVar1 - param_2;
    local_14[3] = in_EAX * 2;
    iVar2 = param_2 + 1;
  }
  while (iVar2 = iVar2 + -1, iVar2 != 0) {
    *param_1 = Translucency_Table[*param_1][param_3];
    param_1 = param_1 + local_14[-(iVar1 >> 0x1f)];
    iVar1 = iVar1 + local_14[2 - (iVar1 >> 0x1f)];
  }
  return;
}
