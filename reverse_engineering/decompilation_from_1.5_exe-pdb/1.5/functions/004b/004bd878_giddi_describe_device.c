/*
 * Entry: 004bd878
 * Name: giddi_describe_device
 * Namespace: Global
 * Signature: int giddi_describe_device(int param_1, _GIDDI_DEVDESC * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl giddi_describe_device(int param_1,_GIDDI_DEVDESC *param_2)

{
  param_2->num_analog = 4;
  param_2->num_discrete = 9;
  sprintf(param_2->short_name,"mouse");
  sprintf(param_2->long_name,"Mouse");
  sprintf(param_2->class_name,"mouse");
  param_2->analog_desc = analogDescriptions;
  param_2->analog_names = analogNames;
  param_2->discrete_desc = discreteDescriptions;
  param_2->discrete_names = discreteNames;
  param_2->data = &mouseData;
  return 0;
}
