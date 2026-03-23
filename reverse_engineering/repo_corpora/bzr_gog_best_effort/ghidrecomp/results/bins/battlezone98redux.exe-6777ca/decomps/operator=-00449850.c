
/* Library Function - Single Match
    public: class boost::exception_detail::refcount_ptr<struct
   boost::exception_detail::error_info_container> & __thiscall
   boost::exception_detail::refcount_ptr<struct
   boost::exception_detail::error_info_container>::operator=(class
   boost::exception_detail::refcount_ptr<struct boost::exception_detail::error_info_container> const
   &)
   
   Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release, Visual Studio 2019 Debug, Visual
   Studio 2019 Release */

refcount_ptr<struct_boost::exception_detail::error_info_container> * __thiscall
boost::exception_detail::refcount_ptr<struct_boost::exception_detail::error_info_container>::
operator=(refcount_ptr<struct_boost::exception_detail::error_info_container> *this,
         refcount_ptr<struct_boost::exception_detail::error_info_container> *param_1)

{
  adopt(this,*(error_info_container **)param_1);
  return this;
}

