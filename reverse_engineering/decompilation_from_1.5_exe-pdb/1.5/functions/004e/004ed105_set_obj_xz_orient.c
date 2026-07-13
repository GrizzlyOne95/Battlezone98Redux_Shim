/*
 * Entry: 004ed105
 * Name: set_obj_xz_orient
 * Namespace: Global
 * Signature: void set_obj_xz_orient(_OBJ76 * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl set_obj_xz_orient(_OBJ76 *param_1,float param_2)

{
  VECTOR_3D VVar1;
  VECTOR_3D VVar2;
  SINCOS SVar3;
  undefined4 local_c;
  
  SVar3 = SinCos(param_2);
  VVar1.z = SVar3.Cos;
  VVar1.x = (float)(int)((ulonglong)SVar3 & 0xffffffff);
  VVar1.y = (float)(int)(((ulonglong)SVar3 & 0xffffffff) >> 0x20);
  set_obj_front(param_1,VVar1);
  set_obj_up(param_1,(VECTOR_3D)ZEXT812(0x3f80000000000000));
  local_c = SVar3.Sin;
  VVar2.z = -local_c;
  VVar2.x = (float)(int)((ulonglong)SVar3 >> 0x20);
  VVar2.y = (float)(int)(((ulonglong)SVar3 >> 0x20) >> 0x20);
  set_obj_right(param_1,VVar2);
  return;
}
