/*
 * Entry: 004c78ec
 * Name: WorldCircle
 * Namespace: Global
 * Signature: void WorldCircle(VECTOR_3D * param_1, float param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl WorldCircle(VECTOR_3D *param_1,float param_2,long param_3)

{
  WorldInterface *pWVar1;
  VECTOR_3D *pVVar2;
  undefined1 local_10 [4];
  long local_c;
  int local_8;
  
  pVVar2 = param_1;
  pWVar1 = WorldInterface::currentDisplay;
  (**(code **)(*(int *)WorldInterface::currentDisplay + 0x20))
            (param_1->x,param_1->z,&param_1,&local_c);
  (**(code **)(*(int *)pWVar1 + 0x20))(pVVar2->x + param_2,pVVar2->z,&local_8,local_10);
  Graphic_Circle(DisplayInterface::currentBuffer,(long)param_1,local_c,local_8 - (int)param_1,0x18,
                 param_3,SOLID_PIXELS);
  return;
}
