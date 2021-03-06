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

#include <bitset>

#include <flecsi/utils/offset.h>

namespace flecsi {
namespace data {

using sparse_data_offset_t = utils::offset__<16>;

template<typename T>
struct sparse_entry_value__ {
  using index_t = uint64_t;

  sparse_entry_value__(index_t entry) : entry(entry) {}

  sparse_entry_value__(index_t entry, T value) : entry(entry), value(value) {}

  sparse_entry_value__() {}

  bool operator<(const sparse_entry_value__ & ev) const {
    return entry < ev.entry;
  }

  index_t entry;
  T value;
};

// Generic bitfield type
using bitset_t = std::bitset<8>;

} // namespace data
} // namespace flecsi

/*~-------------------------------------------------------------------------~-*
 *~-------------------------------------------------------------------------~-*/
