/*
 * Entry: 004e6241
 * Name: std::_Find<SpawnPoint_*_*,SpawnPoint_*>
 * Namespace: std
 * Signature: SpawnPoint * * _Find<SpawnPoint_*_*,SpawnPoint_*>(SpawnPoint * * param_1, SpawnPoint * * param_2, SpawnPoint * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SpawnPoint ** __cdecl
std::_Find<SpawnPoint_*_*,SpawnPoint_*>
          (SpawnPoint **param_1,SpawnPoint **param_2,SpawnPoint **param_3)

{
  if (param_1 != param_2) {
    do {
      if (*param_1 == *param_3) {
        return param_1;
      }
      param_1 = param_1 + 1;
    } while (param_1 != param_2);
  }
  return param_1;
}
