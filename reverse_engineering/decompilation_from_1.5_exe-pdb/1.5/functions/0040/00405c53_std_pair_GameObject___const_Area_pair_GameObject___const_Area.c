/*
 * Entry: 00405c53
 * Name: std::pair<GameObject_*_const,Area>::pair<GameObject_*_const,Area>
 * Namespace: std::pair<GameObject_*_const,Area>
 * Signature: pair<GameObject_*_const,Area> * pair<GameObject_*_const,Area>(pair<GameObject_*_const,Area> * this, GameObject * * param_1, Area * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<GameObject_*_const,Area> * __thiscall
std::pair<GameObject_*_const,Area>::pair<GameObject_*_const,Area>
          (pair<GameObject_*_const,Area> *this,GameObject **param_1,Area *param_2)

{
  this->first = *param_1;
  (this->second).x0 = param_2->x0;
  (this->second).z0 = param_2->z0;
  (this->second).x1 = param_2->x1;
  (this->second).z1 = param_2->z1;
  return this;
}
