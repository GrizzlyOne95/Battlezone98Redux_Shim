/*
 * Entry: 0045f0e4
 * Name: SetPosition
 * Namespace: Global
 * Signature: void SetPosition(int param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetPosition(int param_1,char *param_2,int param_3)

{
  bool bVar1;
  GameObject *this;
  int unaff_EDI;
  VECTOR_3D local_10;
  
  this = GameObjectHandle::GetObj(param_1);
  if (this != (GameObject *)0x0) {
    AiPath::Find(param_2);
    bVar1 = GetPosition((VECTOR_3D *)param_3,(AiPath *)param_2,unaff_EDI);
    if (bVar1) {
      GameObject::SetOrigin(this,&local_10);
    }
  }
  return;
}
