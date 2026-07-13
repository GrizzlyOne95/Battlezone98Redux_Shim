/*
 * Entry: 004d5be8
 * Name: PathDisplay::DrawCommand
 * Namespace: PathDisplay
 * Signature: void DrawCommand(PathDisplay * this, GameObject * param_1, AiCmdInfo * param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
PathDisplay::DrawCommand(PathDisplay *this,GameObject *param_1,AiCmdInfo *param_2,long param_3)

{
  GameObject *pGVar1;
  
  if (param_2->who != 0) {
    pGVar1 = GameObjectHandle::GetObj(param_2->who);
    if (pGVar1 != (GameObject *)0x0) {
      DrawObject(this,pGVar1,true,param_3);
    }
  }
  return;
}
