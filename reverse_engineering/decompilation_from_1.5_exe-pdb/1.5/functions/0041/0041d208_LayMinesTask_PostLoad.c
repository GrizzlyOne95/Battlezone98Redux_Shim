/*
 * Entry: 0041d208
 * Name: LayMinesTask::PostLoad
 * Namespace: LayMinesTask
 * Signature: bool PostLoad(LayMinesTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall LayMinesTask::PostLoad(LayMinesTask *this)

{
  bool bVar1;
  
  bVar1 = GoPoints::PostLoad((GoPoints *)this);
  return bVar1;
}
