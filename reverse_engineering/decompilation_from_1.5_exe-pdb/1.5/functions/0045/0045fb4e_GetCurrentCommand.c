/*
 * Entry: 0045fb4e
 * Name: GetCurrentCommand
 * Namespace: Global
 * Signature: AiCommand GetCurrentCommand(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiCommand __cdecl GetCurrentCommand(int param_1)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 == (GameObject *)0x0) {
    return CMD_NONE;
  }
  return (pGVar1->curCmd).what;
}
