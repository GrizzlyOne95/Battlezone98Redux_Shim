/*
 * Entry: 004e6507
 * Name: std::fill<SpawnPoint_*_*,SpawnPoint_*>
 * Namespace: std
 * Signature: void fill<SpawnPoint_*_*,SpawnPoint_*>(SpawnPoint * * param_1, SpawnPoint * * param_2, SpawnPoint * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::fill<SpawnPoint_*_*,SpawnPoint_*>
          (SpawnPoint **param_1,SpawnPoint **param_2,SpawnPoint **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
