/*
 * Entry: 00518b42
 * Name: std::fill<ObjectClassInfo_*_*,ObjectClassInfo_*>
 * Namespace: std
 * Signature: void fill<ObjectClassInfo_*_*,ObjectClassInfo_*>(ObjectClassInfo * * param_1, ObjectClassInfo * * param_2, ObjectClassInfo * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::fill<ObjectClassInfo_*_*,ObjectClassInfo_*>
          (ObjectClassInfo **param_1,ObjectClassInfo **param_2,ObjectClassInfo **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
