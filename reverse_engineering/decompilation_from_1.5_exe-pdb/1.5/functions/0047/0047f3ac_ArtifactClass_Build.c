/*
 * Entry: 0047f3ac
 * Name: ArtifactClass::Build
 * Namespace: ArtifactClass
 * Signature: GameObject * Build(ArtifactClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall ArtifactClass::Build(ArtifactClass *this,_OBJ76 *param_1)

{
  Artifact *pAVar1;
  
  pAVar1 = GameObject::operator_new(0x230);
  if (pAVar1 == (Artifact *)0x0) {
    pAVar1 = (Artifact *)0x0;
  }
  else {
    pAVar1 = Artifact::Artifact(pAVar1,param_1,this);
  }
  return (GameObject *)pAVar1;
}
