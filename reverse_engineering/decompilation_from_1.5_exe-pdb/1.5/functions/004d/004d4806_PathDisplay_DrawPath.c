/*
 * Entry: 004d4806
 * Name: PathDisplay::DrawPath
 * Namespace: PathDisplay
 * Signature: void DrawPath(PathDisplay * this, AiPath * param_1, int param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::DrawPath(PathDisplay *this,AiPath *param_1,int param_2,long param_3)

{
  undefined1 *puVar1;
  float fVar2;
  AiPath *pAVar3;
  AiPath *pAVar4;
  int iVar5;
  undefined1 *puVar6;
  int iVar7;
  AiPath *local_10;
  long local_c;
  int local_8;
  
  pAVar3 = param_1;
  fVar2 = spriteZ;
  if (param_2 == 0) {
    spriteZ = 0.5;
  }
  else {
    spriteZ = 0.4;
  }
  (**(code **)(this->_padding_ + 0x20))(param_1->points->x,param_1->points->z,&local_8,&param_1);
  iVar5 = local_8;
  pAVar4 = param_1;
  puVar1 = &param_1[-1].me.field_0x5;
  puVar6 = (undefined1 *)((int)&param_1->label + 3);
  if (param_2 == 0) {
    Graphic_Rect_Filled(DisplayInterface::currentBuffer,local_8 + -3,(long)puVar1,local_8 + 3,
                        (long)puVar6,param_3,SOLID_PIXELS);
  }
  else {
    Graphic_Rect_Empty(DisplayInterface::currentBuffer,local_8 + -3,(long)puVar1,local_8 + 3,
                       (long)puVar6,param_3,SOLID_PIXELS);
  }
  iVar7 = 1;
  if (1 < pAVar3->pointCount) {
    do {
      (**(code **)(this->_padding_ + 0x20))
                (pAVar3->points[iVar7].x,pAVar3->points[iVar7].z,&local_c,&local_10);
      Graphic_Line(DisplayInterface::currentBuffer,local_8,(long)param_1,local_c,(long)local_10,
                   param_3,SOLID_PIXELS);
      puVar1 = &local_10[-1].me.field_0x5;
      puVar6 = (undefined1 *)((int)&local_10->label + 3);
      if (param_2 == iVar7) {
        Graphic_Rect_Filled(DisplayInterface::currentBuffer,local_c + -3,(long)puVar1,local_c + 3,
                            (long)puVar6,param_3,SOLID_PIXELS);
      }
      else {
        Graphic_Rect_Empty(DisplayInterface::currentBuffer,local_c + -3,(long)puVar1,local_c + 3,
                           (long)puVar6,param_3,SOLID_PIXELS);
      }
      local_8 = local_c;
      param_1 = local_10;
      iVar7 = iVar7 + 1;
    } while (iVar7 < pAVar3->pointCount);
  }
  if (pAVar3->label != (char *)0x0) {
    if (param_2 < 0) {
      spriteZ = 0.2;
      iVar7 = 2;
    }
    else {
      spriteZ = 0.15;
      iVar7 = 0;
    }
    Graphic_Text(DisplayInterface::currentBuffer,iVar5,(long)((int)&pAVar4->pointCount + 1),&local_8
                 ,(long *)&param_1,pAVar3->label,DisplayInterface::textFont,
                 DisplayInterface::colorWhite,DisplayInterface::colorBlack,iVar7,1,0);
  }
  spriteZ = fVar2;
  return;
}
