/*
 * Entry: 00481b5e
 * Name: DistanceBump
 * Namespace: Global
 * Signature: int DistanceBump(_gas_object * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl DistanceBump(_gas_object *param_1)

{
  VECTOR_3D VVar1;
  bool bVar2;
  int in_EAX;
  VECTOR_3D *pVVar3;
  uint uVar4;
  VECTOR_3D local_1c;
  float local_10;
  float local_c;
  float local_8;
  
  if (((*(_OBJ76 **)(in_EAX + 0x5c) == (_OBJ76 *)0x0) || (*(int *)(in_EAX + 0x3c) == 1)) ||
     ((*(uint *)(in_EAX + 0x14) & 0x400) != 0)) {
    uVar4 = 0;
  }
  else {
    local_10 = (float)View_Record.MainCam.View_Pyramid[0].x;
    local_c = (float)View_Record.MainCam.View_Pyramid[0].y;
    local_8 = (float)View_Record.MainCam.View_Pyramid[0].z;
    pVVar3 = obj_get_world_position(&local_1c,*(_OBJ76 **)(in_EAX + 0x5c));
    VVar1.y = local_c;
    VVar1.x = local_10;
    VVar1.z = local_8;
    bVar2 = TooFar(VVar1,*pVVar3);
    uVar4 = (uint)bVar2;
  }
  return uVar4;
}
