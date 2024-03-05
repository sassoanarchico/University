#include "pose_message.h"
namespace mini_core {
  PoseMessage::PoseMessage():
    SETUP_PROPERTY(pose_vector, Vector6f::Zero()){
  }

  PoseMessage::~PoseMessage(){}

}
