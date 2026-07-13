/*
 * Entry: 004c15d0
 * Name: SelectionDisplay::Init
 * Namespace: SelectionDisplay
 * Signature: void Init(SelectionDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SelectionDisplay::Init(SelectionDisplay *this)

{
  int iVar1;
  
  iVar1 = GetSpriteIndex("object.W");
  this->objectIndex = iVar1;
  iVar1 = GetSpriteIndex("select.W");
  this->selectIndex = iVar1;
  iVar1 = GetSpriteIndex("target.W");
  this->targetIndex = iVar1;
  iVar1 = GetSpriteIndex("caret_u.W");
  this->caretIndex[0] = iVar1;
  iVar1 = GetSpriteIndex("caret_l.W");
  this->caretIndex[1] = iVar1;
  iVar1 = GetSpriteIndex("caret_r.W");
  this->caretIndex[2] = iVar1;
  iVar1 = GetSpriteIndex("caret_d.W");
  this->caretIndex[3] = iVar1;
  iVar1 = GetSpriteIndex("grnbar");
  this->gaugeGreen = iVar1;
  iVar1 = GetSpriteIndex("yelbar");
  this->gaugeYellow = iVar1;
  iVar1 = GetSpriteIndex("redbar");
  this->gaugeRed = iVar1;
  return;
}
