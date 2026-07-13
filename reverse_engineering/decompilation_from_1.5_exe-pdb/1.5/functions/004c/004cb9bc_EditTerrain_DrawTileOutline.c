/*
 * Entry: 004cb9bc
 * Name: EditTerrain::DrawTileOutline
 * Namespace: EditTerrain
 * Signature: void DrawTileOutline(EditTerrain * this, VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EditTerrain::DrawTileOutline(EditTerrain *this,VECTOR_3D *param_1)

{
  long lVar1;
  CAMERA *pCVar2;
  long *plVar3;
  tagPOINT tVar4;
  VECTOR_3D local_c4 [9];
  VECTOR_3D local_58;
  long local_4c [5];
  long local_38;
  long local_34;
  long local_30;
  long local_2c;
  long local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_58.z = spriteZ;
  GetTileXYZ(local_c4,param_1->x,param_1->z);
  plVar3 = local_4c;
  pCVar2 = (CAMERA *)local_c4;
  param_1 = (VECTOR_3D *)0x9;
  do {
    tVar4 = WorldToScreen(this,&local_58,pCVar2);
    lVar1 = ((long *)tVar4.x)[1];
    *plVar3 = *(long *)tVar4.x;
    plVar3[1] = lVar1;
    pCVar2 = (CAMERA *)&pCVar2->Const_y;
    plVar3 = plVar3 + 2;
    param_1 = (VECTOR_3D *)((int)&param_1[-1].z + 3);
  } while (param_1 != (VECTOR_3D *)0x0);
  spriteZ = 0.5;
  Graphic_Line(DisplayInterface::currentBuffer,local_4c[0],local_4c[1],local_4c[2],local_4c[3],
               DisplayInterface::colorWhite,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,local_4c[2],local_4c[3],local_4c[4],local_38,
               DisplayInterface::colorWhite,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,local_4c[4],local_38,(long)local_24,(long)local_20,
               DisplayInterface::colorWhite,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,(long)local_24,(long)local_20,(long)local_c,
               (long)local_8,DisplayInterface::colorWhite,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,(long)local_c,(long)local_8,(long)local_14,
               (long)local_10,DisplayInterface::colorWhite,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,(long)local_14,(long)local_10,(long)local_1c,
               (long)local_18,DisplayInterface::colorWhite,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,(long)local_1c,(long)local_18,local_4c[0],local_4c[1]
               ,DisplayInterface::colorWhite,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,local_34,local_30,local_2c,local_28,this->colorDKGREY
               ,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,local_2c,local_28,(long)local_24,(long)local_20,
               this->colorDKGREY,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,local_4c[2],local_4c[3],local_2c,local_28,
               this->colorDKGREY,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,local_2c,local_28,(long)local_14,(long)local_10,
               this->colorDKGREY,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,local_34,local_30,(long)local_14,(long)local_10,
               DisplayInterface::colorGrey,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,local_4c[0],local_4c[1],local_2c,local_28,
               DisplayInterface::colorGrey,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,local_2c,local_28,(long)local_c,(long)local_8,
               DisplayInterface::colorGrey,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,local_4c[2],local_4c[3],(long)local_24,(long)local_20
               ,DisplayInterface::colorGrey,SOLID_PIXELS);
  spriteZ = local_58.z;
  return;
}
