#pragma once

#include <string>
#include <iostream>
#include <memory>
#include "utils/property_container.h"
#include "geometry/geometry_defs.h"
#include "geometry/geometry3d.h"

namespace mini_core {

  class BaseSensorMessage: public PropertyContainerSerializable {
  public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    BaseSensorMessage(const std::string& topic_ = "",
                      const std::string& frame_id_ = "",
                      int seq_ = -1,
                      const double& timestamp_ = -1);

    PropertyString topic;
    PropertyString frame_id;
    PropertyInt seq;
    PropertyDouble timestamp;
  };

  typedef std::shared_ptr<BaseSensorMessage> BaseSensorMessagePtr;
  typedef std::vector<BaseSensorMessagePtr> BaseSensorMessagePtrVector;

} /* namespace mini_core */

