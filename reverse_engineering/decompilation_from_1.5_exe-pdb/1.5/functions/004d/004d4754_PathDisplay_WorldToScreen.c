/*
 * Entry: 004d4754
 * Name: PathDisplay::WorldToScreen
 * Namespace: PathDisplay
 * Signature: void WorldToScreen(PathDisplay * this, float param_1, float param_2, long * param_3, long * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
PathDisplay::WorldToScreen
          (PathDisplay *this,float param_1,float param_2,long *param_3,long *param_4)

{
  int extraout_EAX;
  int extraout_EAX_00;
  
  _ftol2_sse();
  *param_3 = extraout_EAX + this->screenX0;
  _ftol2_sse();
  *param_4 = this->screenY0 - extraout_EAX_00;
  return;
}
