/*
 * Entry: 004d75c3
 * Name: PathDisplay::DoControlPath
 * Namespace: PathDisplay
 * Signature: void DoControlPath(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall PathDisplay::DoControlPath(PathDisplay *this)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  void *_Dst;
  int iVar4;
  bool bVar5;
  AiPath **ppAVar6;
  AiPath *pAVar7;
  int iVar8;
  AOI *this_00;
  uint uVar9;
  int iVar10;
  _Const_iterator<1> local_a0;
  _Const_iterator<1> local_98;
  float local_90;
  float local_8c;
  char local_88 [12];
  undefined1 local_7c [116];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_7c;
  (this->editRect).right = 10;
  iVar8 = DisplayInterface::currentBuffer->Height;
  (this->editRect).bottom = iVar8 + -0x28;
  this->taskSubjectHandle = 0x104;
  this->taskWhat = iVar8 - CMD_HUNT;
  if (command_controls.cmd_click[0] == '\0') {
    if ((((command_controls.cmd_hold[0] != '\0') && (this->editSelect != 0)) &&
        (-1 < (this->editRect).top)) &&
       (((this->grabOffset).x != (float)DisplayInterface::mousePos.x ||
        ((this->grabOffset).z != (float)DisplayInterface::mousePos.y)))) {
      (this->grabOffset).x = (float)DisplayInterface::mousePos.x;
      (this->grabOffset).z = (float)DisplayInterface::mousePos.y;
      (**(code **)(this->_padding_ + 0x24))
                (DisplayInterface::mousePos.x,DisplayInterface::mousePos.y,&local_8c,&local_90);
      *(float *)(*(int *)(this->editSelect + 8) + (this->editRect).top * 8) =
           local_8c - (float)this->cellColorMap[0];
      *(float *)(*(int *)(this->editSelect + 8) + 4 + (this->editRect).top * 8) =
           local_90 - (float)this->cellColorMap[1];
    }
    goto LAB_004d796c;
  }
  bVar5 = EditPathName(this);
  if (bVar5) goto LAB_004d796c;
  iVar8 = this->editSelect;
  iVar10 = 0;
  if (iVar8 == 0) {
    std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_98,(AiPath::pathList._Myhead)->_Next,&AiPath::pathList);
    local_a0._padding_ = local_98._padding_;
    local_a0._Ptr = local_98._Ptr;
    while( true ) {
      std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::_Const_iterator<1>
                (&local_98,AiPath::pathList._Myhead,&AiPath::pathList);
      bVar5 = std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator==
                        (&local_a0,&local_98);
      if (bVar5) break;
      ppAVar6 = std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator*
                          (&local_a0);
      pAVar7 = *ppAVar6;
      if (pAVar7->label != (char *)0x0) {
        iVar8 = 0;
        if (0 < pAVar7->pointCount) {
          do {
            (**(code **)(this->_padding_ + 0x20))
                      (pAVar7->points[iVar8].x,pAVar7->points[iVar8].z,&local_8c,&local_90);
            uVar9 = (int)local_8c - DisplayInterface::mousePos.x >> 0x1f;
            if (((int)(((int)local_8c - DisplayInterface::mousePos.x ^ uVar9) - uVar9) < 4) &&
               (uVar9 = (int)local_90 - DisplayInterface::mousePos.y >> 0x1f,
               (int)(((int)local_90 - DisplayInterface::mousePos.y ^ uVar9) - uVar9) < 4)) {
              SetEditPath(this,pAVar7);
              (this->editRect).top = iVar8;
              break;
            }
            iVar8 = iVar8 + 1;
          } while (iVar8 < pAVar7->pointCount);
        }
        if (this->editSelect != 0) goto LAB_004d76dc;
      }
      std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator++(&local_a0);
    }
    if (this->editSelect == 0) {
      (this->editRect).left = (this->editRect).left + 1;
      sprintf(local_88,"path_%d",(this->editRect).left);
      pAVar7 = operator_new(0x1c);
      if (pAVar7 == (AiPath *)0x0) {
        pAVar7 = (AiPath *)0x0;
      }
      else {
        pAVar7 = AiPath::AiPath(pAVar7,local_88,1);
      }
      pAVar7->pointCount = 0;
      SetEditPath(this,pAVar7);
      goto LAB_004d7841;
    }
LAB_004d76dc:
    piVar1 = this->cellColorMap + 1;
    piVar2 = this->cellColorMap;
    (**(code **)(this->_padding_ + 0x24))
              (DisplayInterface::mousePos.x,DisplayInterface::mousePos.y,piVar2,piVar1);
    iVar8 = (this->editRect).top * 8;
    *piVar2 = (int)((float)*piVar2 - *(float *)(iVar8 + *(int *)(this->editSelect + 8)));
    *piVar1 = (int)((float)*piVar1 - *(float *)(iVar8 + 4 + *(int *)(this->editSelect + 8)));
  }
  else {
    if (0 < *(int *)(iVar8 + 4)) {
      do {
        puVar3 = (undefined4 *)(*(int *)(iVar8 + 8) + iVar10 * 8);
        (**(code **)(this->_padding_ + 0x20))(*puVar3,puVar3[1],&local_90,&local_8c);
        uVar9 = (int)local_90 - DisplayInterface::mousePos.x >> 0x1f;
        if (((int)(((int)local_90 - DisplayInterface::mousePos.x ^ uVar9) - uVar9) < 4) &&
           (uVar9 = (int)local_8c - DisplayInterface::mousePos.y >> 0x1f,
           (int)(((int)local_8c - DisplayInterface::mousePos.y ^ uVar9) - uVar9) < 4)) {
          if ((command_controls.cmd_multi == '\0') &&
             ((iVar10 == 0 && ((this->editRect).top == *(int *)(iVar8 + 4) + -1)))) {
            iVar8 = *(int *)(this->editSelect + 4);
            *(int *)(this->editSelect + 4) = iVar8 + 1;
            puVar3 = *(undefined4 **)(this->editSelect + 8);
            puVar3[iVar8 * 2] = *puVar3;
            iVar10 = *(int *)(this->editSelect + 8);
            *(undefined4 *)(iVar10 + 4 + iVar8 * 8) = *(undefined4 *)(iVar10 + 4);
            SetEditPath(this,(AiPath *)0x0);
          }
          else {
            (this->editRect).top = iVar10;
          }
          if (this->editSelect == 0) goto LAB_004d78bf;
          goto LAB_004d76dc;
        }
        iVar10 = iVar10 + 1;
      } while (iVar10 < *(int *)(iVar8 + 4));
    }
LAB_004d7841:
    (**(code **)(this->_padding_ + 0x24))
              (DisplayInterface::mousePos.x,DisplayInterface::mousePos.y,&local_8c,&local_90);
    if (command_controls.cmd_multi == '\0') {
LAB_004d7897:
      iVar8 = *(int *)(this->editSelect + 4);
    }
    else {
      iVar8 = *(int *)(this->editSelect + 4);
      iVar10 = (this->editRect).top;
      if (iVar8 + -1 <= iVar10) goto LAB_004d7897;
      iVar4 = *(int *)(this->editSelect + 8);
      memmove((void *)(iVar4 + 0x10 + iVar10 * 8),(void *)(iVar4 + 8 + iVar10 * 8),
              (iVar8 - iVar10) * 8);
      iVar8 = (this->editRect).top + 1;
    }
    piVar1 = (int *)(this->editSelect + 4);
    *piVar1 = *piVar1 + 1;
    *(float *)(*(int *)(this->editSelect + 8) + iVar8 * 8) = local_8c;
    *(float *)(*(int *)(this->editSelect + 8) + 4 + iVar8 * 8) = local_90;
    (this->editRect).top = iVar8;
LAB_004d78bf:
    this->cellColorMap[0] = 0;
    this->cellColorMap[1] = 0;
  }
  (this->grabOffset).x = (float)DisplayInterface::mousePos.x;
  (this->grabOffset).z = (float)DisplayInterface::mousePos.y;
LAB_004d796c:
  if (command_controls.cmd_click[1] != '\0') {
    SetEditPath(this,(AiPath *)0x0);
  }
  if ((command_controls.cmd_delete != '\0') &&
     (pAVar7 = (AiPath *)this->editSelect, pAVar7 != (AiPath *)0x0)) {
    if (pAVar7->pointCount == 1) {
      SetEditPath(this,(AiPath *)0x0);
      this_00 = AOI::Find(pAVar7);
      if (this_00 != (AOI *)0x0) {
        AOI::~AOI(this_00);
        operator_delete(this_00);
      }
      if (pAVar7 != (AiPath *)0x0) {
        AiPath::~AiPath(pAVar7);
        operator_delete(pAVar7);
      }
    }
    else {
      pAVar7->pointCount = pAVar7->pointCount + -1;
      iVar8 = (this->editRect).top;
      iVar10 = *(int *)(this->editSelect + 4);
      if (iVar8 < iVar10) {
        _Dst = (void *)(*(int *)(this->editSelect + 8) + iVar8 * 8);
        memmove(_Dst,(void *)((int)_Dst + 8),(iVar10 - iVar8) * 8);
      }
      iVar8 = (this->editRect).top;
      if (iVar8 == *(int *)(this->editSelect + 4)) {
        (this->editRect).top = iVar8 + -1;
      }
    }
  }
  DrawPaths(this,false);
  if ((AiPath *)this->editSelect != (AiPath *)0x0) {
    DrawPath(this,(AiPath *)this->editSelect,(this->editRect).top,DisplayInterface::colorRed);
    Graphic_Rect_Filled(DisplayInterface::currentBuffer,(this->editRect).right,
                        (this->editRect).bottom,this->taskSubjectHandle,this->taskWhat,
                        DisplayInterface::colorDkGrey,SOLID_PIXELS);
    Graphic_Text(DisplayInterface::currentBuffer,(this->editRect).right + 2,
                 (this->editRect).bottom + 1,(long *)&local_90,(long *)&local_8c,
                 *(char **)this->editSelect,DisplayInterface::textFont,DisplayInterface::colorWhite,
                 -1,0,0,0);
  }
  return;
}
