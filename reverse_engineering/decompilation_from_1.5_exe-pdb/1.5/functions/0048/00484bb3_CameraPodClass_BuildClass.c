/*
 * Entry: 00484bb3
 * Name: CameraPodClass::BuildClass
 * Namespace: CameraPodClass
 * Signature: GameObjectClass * BuildClass(CameraPodClass * this, long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall CameraPodClass::BuildClass(CameraPodClass *this,long64 param_1)

{
  CameraPodClass *pCVar1;
  undefined4 unaff_ESI;
  
  pCVar1 = operator_new(0x180);
  if (pCVar1 == (CameraPodClass *)0x0) {
    pCVar1 = (CameraPodClass *)0x0;
  }
  else {
    pCVar1 = CameraPodClass(pCVar1,this,CONCAT44(unaff_ESI,param_1._4_4_));
  }
  return (GameObjectClass *)pCVar1;
}
