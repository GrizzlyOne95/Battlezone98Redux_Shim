/*
 * Entry: 004a807f
 * Name: std::_Fill<PowerPlant_*_*,PowerPlant_*>
 * Namespace: std
 * Signature: void _Fill<PowerPlant_*_*,PowerPlant_*>(PowerPlant * * param_1, PowerPlant * * param_2, PowerPlant * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Fill<PowerPlant_*_*,PowerPlant_*>
          (PowerPlant **param_1,PowerPlant **param_2,PowerPlant **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
