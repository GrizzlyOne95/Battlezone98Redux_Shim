/*
 * Entry: 004a809e
 * Name: std::_Find<PowerPlant_*_*,PowerPlant_*>
 * Namespace: std
 * Signature: PowerPlant * * _Find<PowerPlant_*_*,PowerPlant_*>(PowerPlant * * param_1, PowerPlant * * param_2, PowerPlant * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PowerPlant ** __cdecl
std::_Find<PowerPlant_*_*,PowerPlant_*>
          (PowerPlant **param_1,PowerPlant **param_2,PowerPlant **param_3)

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
