/*
 * Entry: 0041d3ce
 * Name: LayMinesTask::`scalar_deleting_destructor'
 * Namespace: LayMinesTask
 * Signature: void * `scalar_deleting_destructor'(LayMinesTask * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall LayMinesTask::_scalar_deleting_destructor_(LayMinesTask *this,uint param_1)

{
  GotoTask::~GotoTask((GotoTask *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
