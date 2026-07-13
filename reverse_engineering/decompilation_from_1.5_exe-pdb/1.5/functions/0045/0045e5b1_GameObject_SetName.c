/*
 * Entry: 0045e5b1
 * Name: GameObject::SetName
 * Namespace: GameObject
 * Signature: void SetName(GameObject * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetName(GameObject *this,char *param_1)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  int iVar4;
  
  if (this->label != (char *)0x0) {
    operator_delete__(this->name);
  }
  pcVar2 = param_1;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar3 = operator_new__((uint)(pcVar2 + (1 - (int)(param_1 + 1))));
  this->name = pcVar3;
  pcVar2 = param_1;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
    *pcVar3 = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  iVar4 = GetSpriteIndex(param_1);
  this->nameIndex = iVar4;
  return;
}
