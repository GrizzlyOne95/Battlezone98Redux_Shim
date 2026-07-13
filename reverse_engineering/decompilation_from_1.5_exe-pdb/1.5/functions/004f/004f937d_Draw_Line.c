/*
 * Entry: 004f937d
 * Name: Draw_Line
 * Namespace: Global
 * Signature: void Draw_Line(uchar * param_1, long param_2, long param_3, long param_4, long param_5, long param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Draw_Line(uchar *param_1,long param_2,long param_3,long param_4,long param_5,long param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_14;
  long local_10;
  int local_c [2];
  
  if (param_2 < param_3) {
    iVar2 = param_2 * 2 - param_3;
    local_14 = param_4 + param_5;
    local_10 = param_5;
    local_c[1] = param_2 * 2;
    local_c[0] = iVar2 - param_3;
    param_2 = param_3;
  }
  else {
    iVar2 = param_3 * 2 - param_2;
    local_14 = param_5 + param_4;
    local_10 = param_4;
    local_c[1] = param_3 * 2;
    local_c[0] = iVar2 - param_2;
  }
  iVar3 = param_2 + 1;
  while( true ) {
    iVar1 = iVar2 >> 0x1f;
    iVar3 = iVar3 + -1;
    if (iVar3 == 0) break;
    iVar2 = iVar2 + local_c[-iVar1];
    iVar1 = (&local_14)[-iVar1];
    *param_1 = (uchar)param_6;
    param_1 = param_1 + iVar1;
  }
  return;
}
