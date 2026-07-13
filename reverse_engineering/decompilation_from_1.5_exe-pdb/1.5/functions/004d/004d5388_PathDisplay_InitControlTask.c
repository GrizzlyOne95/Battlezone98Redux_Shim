/*
 * Entry: 004d5388
 * Name: PathDisplay::InitControlTask
 * Namespace: PathDisplay
 * Signature: void InitControlTask(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::InitControlTask(PathDisplay *this)

{
  int iVar1;
  int iVar2;
  
  this->dblTime = -1.0;
  this->taskWhoHandle = 0;
  this->taskPath = (AiPath *)0x0;
  (this->taskWhere).x = 0.0;
  (this->taskWhere).y = 0.0;
  btnX0 = 0;
  btnX1 = (DisplayInterface::currentBuffer->Pane).x1 - (DisplayInterface::currentBuffer->Pane).x0;
  iVar1 = (DisplayInterface::currentBuffer->Pane).y1;
  iVar2 = (DisplayInterface::currentBuffer->Pane).y0;
  (this->prevMousePos).y = 0;
  btnY0 = iVar1 - iVar2;
  return;
}
