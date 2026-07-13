/*
 * Entry: 0041d0c6
 * Name: LayMinesTask::LayMinesTask
 * Namespace: LayMinesTask
 * Signature: LayMinesTask * LayMinesTask(LayMinesTask * this, Craft * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LayMinesTask * __thiscall LayMinesTask::LayMinesTask(LayMinesTask *this,Craft *param_1)

{
  float *pfVar1;
  
  GoPoints::GoPoints((GoPoints *)this,param_1);
  this->mine = 0;
  this->radius = 60.0;
  this->radiusInc = 60.0;
  this->_padding_ = (int)&_vftable_;
  this->angleInc = 1.2566371;
  this->mineCount = 0xf;
  this->angleDec = 0.0;
  this->angle = 0.0;
  pfVar1 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  (this->center).x = *pfVar1;
  (this->center).y = pfVar1[1];
  (this->center).z = pfVar1[2];
  return this;
}
