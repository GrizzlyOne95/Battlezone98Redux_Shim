/*
 * Entry: 004d5097
 * Name: PathDisplay::DoControlPlan
 * Namespace: PathDisplay
 * Signature: void DoControlPlan(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall PathDisplay::DoControlPlan(PathDisplay *this)

{
  undefined4 *puVar1;
  float fVar2;
  float fVar3;
  DWORD DVar4;
  int iVar5;
  AiPath *pAVar6;
  long lVar7;
  long local_98;
  long local_94;
  float local_90;
  float local_8c;
  char local_88 [12];
  undefined1 local_7c [116];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_7c;
  if (command_controls.cmd_click[0] != '\0') {
    (**(code **)(this->_padding_ + 0x24))
              (DisplayInterface::mousePos.x,DisplayInterface::mousePos.y,&local_90);
    if (this->planX0 == 1e+30) {
      this->planX0 = local_90;
      this->planZ0 = local_8c;
    }
    else if (this->planX1 == 1e+30) {
      pAVar6 = (AiPath *)this->editPathCount;
      this->planX1 = local_90;
      this->planZ1 = local_8c;
      if (pAVar6 != (AiPath *)0x0) {
        AiPath::~AiPath(pAVar6);
        operator_delete(pAVar6);
      }
      DVar4 = timeGetTime();
      this->planTime = DVar4;
      iVar5 = this->buildTeam;
      if (iVar5 < 0) {
        iVar5 = 1;
      }
      pAVar6 = FindPlan(this->planX0,this->planZ0,this->planX1,this->planZ1,0,iVar5);
      this->editPathCount = (int)pAVar6;
      DVar4 = timeGetTime();
      fVar2 = this->planZ1 - this->planZ0;
      fVar3 = this->planX1 - this->planX0;
      this->planTime = DVar4 - this->planTime;
      this->planPath = (AiPath *)SQRT(fVar3 * fVar3 + fVar2 * fVar2);
      if ((AiPath *)this->editPathCount == (AiPath *)0x0) {
        pAVar6 = (AiPath *)0x0;
      }
      else {
        pAVar6 = (AiPath *)AiPath::GetLength((AiPath *)this->editPathCount);
      }
      this->editPath = pAVar6;
      this->planX0 = 1e+30;
      this->planX1 = 1e+30;
    }
  }
  if (this->planX0 != 1e+30) {
    (**(code **)(this->_padding_ + 0x20))(this->planX0,this->planZ0,&local_90);
    Graphic_Rect_Empty(DisplayInterface::currentBuffer,(int)local_90 + -3,(int)local_8c + -3,
                       (int)local_90 + 3,(int)local_8c + 3,DisplayInterface::colorGreen,SOLID_PIXELS
                      );
  }
  pAVar6 = (AiPath *)this->editPathCount;
  if (pAVar6 != (AiPath *)0x0) {
    lVar7 = DisplayInterface::colorRed;
    if (pAVar6->pathType != BAD_PATH) {
      lVar7 = DisplayInterface::colorGreen;
    }
    DrawPath(this,pAVar6,-1,lVar7);
    sprintf(local_88,"Time: %d ms\nDist: %.1f m\nLen: %.1f m",this->planTime,
            (double)(float)this->planPath,(double)(float)this->editPath);
    puVar1 = (undefined4 *)
             (*(int *)(this->editPathCount + 8) + -8 + *(int *)(this->editPathCount + 4) * 8);
    (**(code **)(this->_padding_ + 0x20))(*puVar1,puVar1[1],&local_90);
    Graphic_Text(DisplayInterface::currentBuffer,(long)local_90,(long)local_8c,&local_98,&local_94,
                 local_88,DisplayInterface::textFont,DisplayInterface::colorWhite,
                 DisplayInterface::colorBlack,2,0,0);
  }
  return;
}
