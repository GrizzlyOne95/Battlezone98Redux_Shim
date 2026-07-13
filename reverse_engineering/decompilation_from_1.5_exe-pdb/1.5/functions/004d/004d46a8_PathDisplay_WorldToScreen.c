/*
 * Entry: 004d46a8
 * Name: PathDisplay::WorldToScreen
 * Namespace: PathDisplay
 * Signature: void WorldToScreen(PathDisplay * this, float param_1, float param_2, float param_3, long * param_4, long * param_5, long * param_6, long * param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
PathDisplay::WorldToScreen
          (PathDisplay *this,float param_1,float param_2,float param_3,long *param_4,long *param_5,
          long *param_6,long *param_7)

{
  if (param_3 * this->scale < 1.5) {
    param_3 = 1.5 / this->scale;
  }
  (**(code **)(this->_padding_ + 0x20))(param_1 - param_3,param_2 + param_3,param_4,param_5);
  (**(code **)(this->_padding_ + 0x20))(param_1 + param_3,param_2 - param_3,param_6,param_7);
  return;
}
