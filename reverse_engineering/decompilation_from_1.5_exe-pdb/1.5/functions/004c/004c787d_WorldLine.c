/*
 * Entry: 004c787d
 * Name: WorldLine
 * Namespace: Global
 * Signature: void WorldLine(VECTOR_3D * param_1, VECTOR_3D * param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl WorldLine(VECTOR_3D *param_1,VECTOR_3D *param_2,long param_3)

{
  WorldInterface *pWVar1;
  long local_10;
  long local_c;
  long local_8;
  
  pWVar1 = WorldInterface::currentDisplay;
  (**(code **)(*(int *)WorldInterface::currentDisplay + 0x20))
            (param_1->x,param_1->z,&local_10,&local_c);
  (**(code **)(*(int *)pWVar1 + 0x20))(param_2->x,param_2->z,&local_8,&param_1);
  Graphic_Line(DisplayInterface::currentBuffer,local_10,local_c,local_8,(long)param_1,param_3,
               SOLID_PIXELS);
  return;
}
