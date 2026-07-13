/*
 * Entry: 004c3ef6
 * Name: GameObject::SetSelected
 * Namespace: GameObject
 * Signature: void SetSelected(GameObject * this, bool param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetSelected(GameObject *this,bool param_1)

{
  if (param_1) {
    if (this->isSelected == false) {
      (**(code **)(this->_padding_ + 0x20))();
    }
  }
  else if (this->isSelected != false) {
    (**(code **)(this->_padding_ + 0x24))();
  }
  this->isSelected = param_1;
  return;
}
