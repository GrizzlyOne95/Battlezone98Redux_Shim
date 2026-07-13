/*
 * Entry: 004f9a50
 * Name: Graphic_Circle
 * Namespace: Global
 * Signature: void Graphic_Circle(_GRAPHIC_BUFFER * param_1, long param_2, long param_3, long param_4, long param_5, long param_6, BITMAP_OPER param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Graphic_Circle(_GRAPHIC_BUFFER *param_1,long param_2,long param_3,long param_4,long param_5,
              long param_6,BITMAP_OPER param_7)

{
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int iVar1;
  long local_14;
  long local_10;
  
  if (param_5 < 0xc) {
    param_5 = 0xc;
  }
  if (0x18 < param_5) {
    param_5 = 0x18;
  }
  fcos((float10)6.2831855 / (float10)param_5);
  fsin((float10)6.2831855 / (float10)param_5);
  _ftol2_sse();
  local_10 = param_3;
  if (0 < param_5) {
    local_14 = param_5;
    iVar1 = extraout_EAX + param_2;
    do {
      _ftol2_sse();
      _ftol2_sse();
      Graphic_Line(param_1,iVar1,local_10,extraout_EAX_00 + param_2,extraout_EAX_01 + param_3,
                   param_6,param_7);
      local_14 = local_14 + -1;
      iVar1 = extraout_EAX_00 + param_2;
      local_10 = extraout_EAX_01 + param_3;
    } while (local_14 != 0);
  }
  return;
}
