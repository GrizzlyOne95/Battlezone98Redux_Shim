/*
 * Entry: 004d52cd
 * Name: PathDisplay::EditPathName
 * Namespace: PathDisplay
 * Signature: bool EditPathName(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall PathDisplay::EditPathName(PathDisplay *this)

{
  bool bVar1;
  undefined4 uStack_8;
  
  if ((((this->editSelect == 0) || (DisplayInterface::mousePos.x < (this->editRect).right)) ||
      (this->taskSubjectHandle <= DisplayInterface::mousePos.x)) ||
     ((DisplayInterface::mousePos.y < (this->editRect).bottom ||
      ((int)this->taskWhat <= DisplayInterface::mousePos.y)))) {
    bVar1 = false;
  }
  else {
    uStack_8 = this;
    UnlockMouse();
    PathDialog::PathDialog((PathDialog *)((int)&uStack_8 + 3),(AiPath *)this->editSelect);
    PathDialog::Execute((PathDialog *)((int)&uStack_8 + 3));
    LockMouse();
    PathDialog::~PathDialog((PathDialog *)((int)&uStack_8 + 3));
    bVar1 = true;
  }
  return bVar1;
}
