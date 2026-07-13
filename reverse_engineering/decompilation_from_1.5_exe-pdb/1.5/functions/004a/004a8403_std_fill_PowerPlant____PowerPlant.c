/*
 * Entry: 004a8403
 * Name: std::fill<PowerPlant_*_*,PowerPlant_*>
 * Namespace: std
 * Signature: void fill<PowerPlant_*_*,PowerPlant_*>(PowerPlant * * param_1, PowerPlant * * param_2, PowerPlant * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::fill<PowerPlant_*_*,PowerPlant_*>
          (PowerPlant **param_1,PowerPlant **param_2,PowerPlant **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
