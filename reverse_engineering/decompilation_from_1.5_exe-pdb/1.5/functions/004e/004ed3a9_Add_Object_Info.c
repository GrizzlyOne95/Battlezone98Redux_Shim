/*
 * Entry: 004ed3a9
 * Name: Add_Object_Info
 * Namespace: Global
 * Signature: OBJECT_NODE * Add_Object_Info(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OBJECT_NODE * __cdecl Add_Object_Info(_OBJ76 *param_1)

{
  long lVar1;
  SPHERE *pSVar2;
  _OBJ76 *in_ECX;
  float10 fVar3;
  float10 fVar4;
  float10 fVar5;
  SPHERE local_10;
  
  lVar1 = o_nextfree;
  objectdb[o_nextfree].next = object_table[((int)in_ECX * 0x6cd + 0xaabU) % 0x71];
  object_table[((int)in_ECX * 0x6cd + 0xaabU) % 0x71] = lVar1;
  objectdb[lVar1].obj = in_ECX;
  fVar3 = (float10)(in_ECX->transform).front_x;
  fVar4 = (float10)(in_ECX->transform).front_z;
  fVar5 = (float10)0;
  if ((fVar5 == fVar3) && (fVar5 == fVar4)) {
    objectdb[lVar1].heading = (float)fVar5;
    objectdb[lVar1].orientation = (float)fVar5;
  }
  else {
    fVar5 = (float10)fpatan(fVar3,fVar4);
    objectdb[lVar1].orientation = (float)fVar5;
    objectdb[lVar1].heading = (float)fVar5;
  }
  pSVar2 = Object_WorldSphere(&local_10,in_ECX);
  lVar1 = o_nextfree;
  o_nextfree = o_nextfree + 1;
  objectdb[lVar1].sphere.origin.x = (pSVar2->origin).x;
  objectdb[lVar1].sphere.origin.y = (pSVar2->origin).y;
  objectdb[lVar1].sphere.origin.z = (pSVar2->origin).z;
  objectdb[lVar1].sphere.radius = pSVar2->radius;
  return objectdb + lVar1;
}
