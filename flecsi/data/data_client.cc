/*~--------------------------------------------------------------------------~*
 * Copyright (c) 2015 Los Alamos National Security, LLC
 * All rights reserved.
 *~--------------------------------------------------------------------------~*/

///
/// \file
/// \date Initial file creation: Dec 7, 2016
///

#include "flecsi/data/data_client.h"
#include "flecsi/data/storage.h"

namespace flecsi {
namespace data {

template<>
data_client__<flecsi_data_policy_t>::data_client__(data_client__ && o) : data_client__()
{
  // store old runtime id
  auto rid = o.runtime_id();
  // move the data now
  flecsi::data::storage_t::instance().move( rid, runtime_id() );
}

template<>
data_client__<flecsi_data_policy_t> &
data_client__<flecsi_data_policy_t>::operator=(data_client__ && o)
{
  // store old runtime id
  auto rid = o.runtime_id();
  // move the data now
  flecsi::data::storage_t::instance().move( rid, runtime_id() );
  // return a reference to the new object
  return *this;
}

template<>
void data_client__<flecsi_data_policy_t>::fini() 
{
  flecsi::data::storage_t::instance().reset( runtime_id() );
}

} // namespace data
} // namespace flecsi

/*~-------------------------------------------------------------------------~-*
 * Formatting options for vim.
 * vim: set tabstop=2 shiftwidth=2 expandtab :
 *~-------------------------------------------------------------------------~-*/
