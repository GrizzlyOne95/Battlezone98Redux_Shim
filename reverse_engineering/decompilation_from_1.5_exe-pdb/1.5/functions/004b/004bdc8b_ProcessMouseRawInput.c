/*
 * Entry: 004bdc8b
 * Name: ProcessMouseRawInput
 * Namespace: Global
 * Signature: void ProcessMouseRawInput(tagRAWMOUSE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ProcessMouseRawInput(tagRAWMOUSE *param_1)

{
  ushort uVar1;
  ushort uVar2;
  
  uVar1 = (param_1->field1_0x4)._s_1.usButtonFlags;
  if ((uVar1 & 1) != 0) {
    discreteClrMap = discreteClrMap & 0xfffffffe;
    discreteSetMap = discreteSetMap | 1;
  }
  if ((uVar1 & 2) != 0) {
    discreteClrMap = discreteClrMap | 1;
  }
  if ((uVar1 & 0x10) != 0) {
    discreteClrMap = discreteClrMap & 0xfffffffd;
    discreteSetMap = discreteSetMap | 2;
  }
  if ((uVar1 & 0x20) != 0) {
    discreteClrMap = discreteClrMap | 2;
  }
  if ((uVar1 & 4) != 0) {
    discreteClrMap = discreteClrMap & 0xfffffffb;
    discreteSetMap = discreteSetMap | 4;
  }
  if ((uVar1 & 8) != 0) {
    discreteClrMap = discreteClrMap | 4;
  }
  if ((uVar1 & 0x40) != 0) {
    discreteClrMap = discreteClrMap & 0xfffffff7;
    discreteSetMap = discreteSetMap | 8;
  }
  if ((uVar1 & 0x80) != 0) {
    discreteClrMap = discreteClrMap | 8;
  }
  if ((uVar1 & 0x100) != 0) {
    discreteClrMap = discreteClrMap & 0xffffffef;
    discreteSetMap = discreteSetMap | 0x10;
  }
  if ((uVar1 & 0x200) != 0) {
    discreteClrMap = discreteClrMap | 0x10;
  }
  if ((uVar1 & 0x400) != 0) {
    uVar2 = (param_1->field1_0x4)._s_1.usButtonData;
    if ((short)uVar2 < 1) {
      if ((short)uVar2 < 0) {
        discreteSetMap = discreteSetMap | 0x20;
        discreteClrMap = discreteClrMap | 0x20;
      }
    }
    else {
      discreteSetMap = discreteSetMap | 0x40;
      discreteClrMap = discreteClrMap | 0x40;
    }
  }
  if ((uVar1 & 0x800) != 0) {
    uVar1 = (param_1->field1_0x4)._s_1.usButtonData;
    if ((short)uVar1 < 1) {
      if ((short)uVar1 < 0) {
        discreteSetMap = discreteSetMap | 0x80;
        discreteClrMap = discreteClrMap | 0x80;
      }
    }
    else {
      discreteSetMap = discreteSetMap | 0x100;
      discreteClrMap = discreteClrMap | 0x100;
    }
  }
  if ((param_1->lLastX != 0) || (param_1->lLastY != 0)) {
    deltaX = deltaX + param_1->lLastX;
    deltaY = deltaY + param_1->lLastY;
  }
  return;
}
