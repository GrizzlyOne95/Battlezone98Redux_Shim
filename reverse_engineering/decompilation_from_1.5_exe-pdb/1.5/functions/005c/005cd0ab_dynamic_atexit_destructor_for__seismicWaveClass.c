/*
 * Entry: 005cd0ab
 * Name: `dynamic_atexit_destructor_for_'seismicWaveClass''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'seismicWaveClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__seismicWaveClass__(void)

{
  seismicWaveClass._padding_ = (int)&SeismicWaveClass::_vftable_;
  OrdnanceClass::~OrdnanceClass((OrdnanceClass *)&seismicWaveClass);
  return;
}
