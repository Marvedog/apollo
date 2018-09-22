/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/**
 * @file
 **/

#ifndef MODULES_PLANNING_SMOOTHING_SPLINE_OSQP_SPLINE_2D_SOLVER_H_
#define MODULES_PLANNING_SMOOTHING_SPLINE_OSQP_SPLINE_2D_SOLVER_H_

#include <memory>
#include <vector>

#include "Eigen/Core"
#include "gtest/gtest_prod.h"
#include "osqp/include/osqp.h"

#include "modules/planning/math/smoothing_spline/spline_2d.h"
#include "modules/planning/math/smoothing_spline/spline_2d_solver.h"

namespace apollo {
namespace planning {

class OsqpSpline2dSolver final : public Spline2dSolver {
 public:
  OsqpSpline2dSolver(const std::vector<double>& t_knots, const uint32_t order);

  void Reset(const std::vector<double>& t_knots, const uint32_t order) override;

  // customize setup
  Spline2dConstraint* mutable_constraint() override;
  Spline2dKernel* mutable_kernel() override;
  Spline2d* mutable_spline() override;

  // solve
  bool Solve() override;

  // extract
  const Spline2d& spline() const override;

 private:
  FRIEND_TEST(OSQPSolverTest, basic_test);
  void ToCSCMatrix(const Eigen::MatrixXd& dense_matrix,
                   std::vector<double>* data, std::vector<double>* indices,
                   std::vector<double>* indptr) const;

 private:
  OSQPSettings* osqp_settings_ = nullptr;
  OSQPWorkspace* work_ = nullptr;  // Workspace
  OSQPData* data_ = nullptr;       // OSQPData

  int last_num_constraint_ = 0;
  int last_num_param_ = 0;
  bool last_problem_success_ = false;
};

}  // namespace planning
}  // namespace apollo

#endif  // MODULES_PLANNING_SMOOTHING_SPLINE_OSQP_SPLINE_2D_SOLVER_H_