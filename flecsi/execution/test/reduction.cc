/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2014 Los Alamos National Security, LLC
 * All rights reserved.
 *~-------------------------------------------------------------------------~~*/

///
/// \file
/// \date Initial file creation: May 4, 2017
///

#include <cinchtest.h>

#include <flecsi/execution/execution.h>


namespace flecsi {
namespace execution {

double local_value_task(
        const int cycle)
{
#if FLECSI_RUNTIME_MODEL == FLECSI_RUNTIME_MODEL_legion
  context_t & context_ = context_t::instance();
  const size_t my_color = context_.color();
#elif FLECSI_RUNTIME_MODEL == FLECSI_RUNTIME_MODEL_mpi
  int my_color;
  MPI_Comm_rank(MPI_COMM_WORLD, &my_color);
#endif
  return static_cast<double>((my_color+1) * cycle);
}

flecsi_register_task(local_value_task, flecsi::execution, loc, index);


template<typename T>
using handle_t = flecsi::execution::flecsi_future<T,
    flecsi::execution::launch_type_t::single>;

void reduction_check_task(handle_t<double> f_max, handle_t<double> f_min,
      int num_colors, int cycle)
{
std::cout <<"IRINA DEBUG"<<std::endl;
    ASSERT_EQ(f_max.get(), static_cast<double>(num_colors * cycle));
    ASSERT_EQ(f_min.get(), static_cast<double>(cycle));
}

flecsi_register_task(reduction_check_task, flecsi::execution, loc, single);

//----------------------------------------------------------------------------//
// User driver.
//----------------------------------------------------------------------------//

void driver(int argc, char ** argv) {

  int num_colors, my_color;
  MPI_Comm_size(MPI_COMM_WORLD, &num_colors);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_color);
  clog(trace) << "Rank " << my_color << " in driver" << std::endl;

  for(int cycle=1; cycle < 10; cycle++) {
    auto global_min_future =
      flecsi_execute_reduction_task(local_value_task, flecsi::execution, index,
          min_redop_id, cycle);

    auto global_max_future =
      flecsi_execute_reduction_task(local_value_task, flecsi::execution, index,
          max_redop_id, cycle);

#if 1
//    auto global_max =
//      flecsi::execution::context_t::instance().reduce_max(global_max_future);

//    double global_min =
//      flecsi::execution::context_t::instance().reduce_min(global_min_future);

    ASSERT_EQ(global_max_future.get(),
        static_cast<double>(num_colors * cycle));
    ASSERT_EQ(global_min_future.get(), static_cast<double>(cycle));
 
   flecsi_execute_task(reduction_check_task, flecsi::execution, single,
     global_max_future, global_min_future, num_colors, cycle); 
#endif
  } // cycle

} // driver

} // namespace execution
} // namespace flecsi

TEST(reduction, testname) {

} // TEST


/*~------------------------------------------------------------------------~--*
 * Formatting options for vim.
 * vim: set tabstop=2 shiftwidth=2 expandtab :
 *~------------------------------------------------------------------------~--*/
