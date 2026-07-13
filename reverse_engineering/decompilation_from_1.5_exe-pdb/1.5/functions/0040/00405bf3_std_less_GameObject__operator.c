/*
 * Entry: 00405bf3
 * Name: std::less<GameObject_*>::operator()
 * Namespace: std::less<GameObject_*>
 * Signature: bool operator()(less<GameObject_*> * this, GameObject * * param_1, GameObject * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::less<GameObject_*>::operator()
          (less<GameObject_*> *this,GameObject **param_1,GameObject **param_2)

{
  return *param_1 < *param_2;
}
