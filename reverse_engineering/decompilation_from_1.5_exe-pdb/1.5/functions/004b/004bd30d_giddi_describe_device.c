/*
 * Entry: 004bd30d
 * Name: giddi_describe_device
 * Namespace: Global
 * Signature: int giddi_describe_device(int param_1, _GIDDI_DEVDESC * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Enum "LOCALE": Some values do not have unique names */

int __cdecl giddi_describe_device(int param_1,_GIDDI_DEVDESC *param_2)

{
  char *_Format;
  
  InitKeyboard(LocaleInfo->KeyNames,LocaleInfo->KeyDescriptions);
  param_2->num_analog = 0;
  param_2->num_discrete = 0x7d;
  sprintf(param_2->short_name,"keyboard");
  _Format = (char *)_StrLookupFind(_DAT_00224566,"Keyboard");
  sprintf(param_2->long_name,_Format);
  sprintf(param_2->class_name,"keyboard");
  param_2->analog_desc = (char **)0x0;
  param_2->analog_names = (char **)0x0;
  param_2->data = (void *)0x0;
  param_2->discrete_desc = discreteDescriptions;
  param_2->discrete_names = discreteNames;
  return 0;
}
