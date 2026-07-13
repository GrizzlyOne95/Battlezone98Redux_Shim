
CCachedDataPathProperty * __thiscall FUN_007076a0(CCachedDataPathProperty *param_1,uint param_2)

{
  CCachedDataPathProperty::~CCachedDataPathProperty(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

