/*
 * Entry: 00405b0d
 * Name: GameObject::GetSpeed
 * Namespace: GameObject
 * Signature: float GetSpeed(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __thiscall GameObject::GetSpeed(GameObject *this)

{
  return (this->euler).v_mag;
}
