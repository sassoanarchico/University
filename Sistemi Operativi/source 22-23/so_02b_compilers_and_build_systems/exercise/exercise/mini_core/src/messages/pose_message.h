#pragma once
#include "utils/property_container.h"
#include "utils/property_eigen.h"
#include "geometry/geometry_defs.h"
#include "geometry/geometry3d.h"
#include "geometry/geometry2d.h"


namespace mini_core {
  class PoseMessage: public PropertyContainerSerializable {
  public:
    PoseMessage();
    virtual ~PoseMessage();

    inline void getPose(Isometry3f& pose_) const { 
      pose_ = geometry3d::v2t(pose_vector.value());
    }

    inline void getPose(Isometry2f& pose_) const { 
      pose_ = geometry3d::get2dFrom3dPose(geometry3d::v2t(pose_vector.value()));
    }

    inline void getPose(Vector6f& pose_) const {
      pose_=pose_vector.value();
    }

    inline void getPose(Vector3f& pose_) const {
      pose_=geometry2d::t2v(geometry3d::get2dFrom3dPose(geometry3d::v2t(pose_vector.value())));
    }

    inline void setPose(const Isometry3f& pose_) {
      pose_vector.setValue(geometry3d::t2v(pose_));
    }

    inline void setPose(const Isometry2f& pose_) {
      pose_vector.setValue(geometry3d::t2v(geometry3d::get3dFrom2dPose(pose_)));
    }

    inline void setPose(const Vector6f& pose_) {
      pose_vector.setValue(pose_);
    }

    inline void setPose(const Vector3f& pose_) {
      pose_vector.setValue(geometry3d::t2v(geometry3d::get3dFrom2dPose(geometry2d::v2t(pose_))));
    }

    PropertyEigen_<Vector6f> pose_vector;
  };

  using PoseMessagePtr = std::shared_ptr<PoseMessage>;
}
