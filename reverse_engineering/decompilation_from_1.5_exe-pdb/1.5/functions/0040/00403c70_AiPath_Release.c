/*
 * Entry: 00403c70
 * Name: AiPath::Release
 * Namespace: AiPath
 * Signature: void Release(AiPath * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AiPath::Release(AiPath *param_1)

{
  if (param_1->label == (char *)0x0) {
    ~AiPath(param_1);
    operator_delete(param_1);
  }
  return;
}
