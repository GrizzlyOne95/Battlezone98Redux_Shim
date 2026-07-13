/*
 * Entry: 004d478d
 * Name: PathDisplay::ScreenToWorld
 * Namespace: PathDisplay
 * Signature: void ScreenToWorld(PathDisplay * this, long param_1, long param_2, float * param_3, float * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
PathDisplay::ScreenToWorld
          (PathDisplay *this,long param_1,long param_2,float *param_3,float *param_4)

{
  *param_3 = (float)(param_1 - this->screenX0) / this->scale + this->worldX0;
  *param_4 = (float)(this->screenY0 - param_2) / this->scale + this->worldZ0;
  return;
}
