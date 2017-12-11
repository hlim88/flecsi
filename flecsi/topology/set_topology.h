/*
    @@@@@@@@  @@           @@@@@@   @@@@@@@@ @@
   /@@/////  /@@          @@////@@ @@////// /@@
   /@@       /@@  @@@@@  @@    // /@@       /@@
   /@@@@@@@  /@@ @@///@@/@@       /@@@@@@@@@/@@
   /@@////   /@@/@@@@@@@/@@       ////////@@/@@
   /@@       /@@/@@//// //@@    @@       /@@/@@
   /@@       @@@//@@@@@@ //@@@@@@  @@@@@@@@ /@@
   //       ///  //////   //////  ////////  //

   Copyright (c) 2016, Los Alamos National Security, LLC
   All rights reserved.
                                                                              */
#pragma once

/*! @file */

#include <flecsi/topology/set_storage.h>
#include <flecsi/topology/set_types.h>
#include <flecsi/topology/set_utils.h>

namespace flecsi {
namespace topology {

template<typename SET_TYPES>
class set_topology_t : public set_topology_base_t<set_storage_t<SET_TYPES>> {
public:
  static const size_t num_index_spaces =
      std::tuple_size<typename SET_TYPES::entity_types_t>::value;

  using storage_t = set_storage_t<SET_TYPES>;

  using base_t = set_topology_base_t<storage_t>;

  using id_t = utils::id_t;

  using type_identifier_t = set_topology_t;

  set_topology_t(){}

  set_topology_t(const set_topology_t& s)
  : base_t(s){}

  void
  initialize_storage(){}
};

} // namespace topology
} // namespace flecsi