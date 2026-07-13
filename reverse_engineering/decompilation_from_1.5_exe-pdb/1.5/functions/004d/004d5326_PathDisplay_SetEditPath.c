/*
 * Entry: 004d5326
 * Name: PathDisplay::SetEditPath
 * Namespace: PathDisplay
 * Signature: void SetEditPath(PathDisplay * this, AiPath * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::SetEditPath(PathDisplay *this,AiPath *param_1)

{
  int iVar1;
  
  if ((AiPath *)this->editSelect != (AiPath *)0x0) {
    AiPath::ShrinkPoints((AiPath *)this->editSelect);
  }
  this->editSelect = (int)param_1;
  if (param_1 != (AiPath *)0x0) {
    iVar1 = param_1->pointCount;
    AiPath::SetPoints(param_1,200);
    *(int *)(this->editSelect + 4) = iVar1;
  }
  return;
}
