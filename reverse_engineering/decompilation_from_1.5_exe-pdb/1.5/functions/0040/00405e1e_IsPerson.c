/*
 * Entry: 00405e1e
 * Name: IsPerson
 * Namespace: Global
 * Signature: int IsPerson(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsPerson(_OBJ76 *param_1)

{
  return (uint)(param_1->class_id == CLASS_ID_PERSON);
}
