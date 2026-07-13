/*
 * Entry: 004acc63
 * Name: giddi_describe_device
 * Namespace: Global
 * Signature: int giddi_describe_device(int param_1, _GIDDI_DEVDESC * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl giddi_describe_device(int param_1,_GIDDI_DEVDESC *param_2)

{
  param_2->num_analog = 0;
  param_2->num_discrete = 3;
  sprintf(param_2->short_name,"program");
  sprintf(param_2->long_name,"Program");
  sprintf(param_2->class_name,"program");
  param_2->data = (void *)0x0;
  param_2->analog_desc = analogDescriptions;
  param_2->analog_names = analogNames;
  param_2->discrete_desc = discreteDescriptions;
  param_2->discrete_names = discreteNames;
  return 0;
}
