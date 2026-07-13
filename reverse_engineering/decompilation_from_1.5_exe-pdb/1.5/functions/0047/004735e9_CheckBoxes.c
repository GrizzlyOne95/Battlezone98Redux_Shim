/*
 * Entry: 004735e9
 * Name: CheckBoxes
 * Namespace: Global
 * Signature: int CheckBoxes(BBOX * param_1, tagENTITY * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CheckBoxes(BBOX *param_1,tagENTITY *param_2)

{
  if (((((param_1->min).x <= (param_2->bBox).max.x) && ((param_2->bBox).min.x <= (param_1->max).x))
      && ((param_1->min).y <= (param_2->bBox).max.y)) &&
     ((((param_2->bBox).min.y <= (param_1->max).y && ((param_1->min).z <= (param_2->bBox).max.z)) &&
      ((param_2->bBox).min.z <= (param_1->max).z)))) {
    return 1;
  }
  return 0;
}
