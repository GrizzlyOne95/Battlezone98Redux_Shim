/*
 * Entry: 004952fa
 * Name: GameObject::SetTeam
 * Namespace: GameObject
 * Signature: void SetTeam(GameObject * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetTeam(GameObject *this,int param_1)

{
  (**(code **)((int)this[-1].maxHealth + 8))();
  (**(code **)((int)this[-1].maxHealth + 4))(param_1);
  return;
}
