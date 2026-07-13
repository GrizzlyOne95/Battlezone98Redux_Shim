/*
 * Entry: 005ca87d
 * Name: `dynamic_initializer_for_'artifactClass''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'artifactClass''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__artifactClass__(void)

{
  ArtifactClass::ArtifactClass(&artifactClass);
  atexit(_dynamic_atexit_destructor_for__artifactClass__);
  return;
}
