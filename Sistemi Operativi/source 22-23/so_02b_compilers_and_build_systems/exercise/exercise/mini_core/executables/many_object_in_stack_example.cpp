#include <iostream>
#include <utils/deserializer.h>
#include <utils/identifiable.h>
#include <utils/property_container_manager.h>
#include <utils/serialization_context.h>
#include <utils/object_data.h>
#include <messages/pose_message.h>
#include <messages/odometry_message.h>
#include <data_structures/matrix.h>

using namespace mini_core;

int main(int argc_, char** argv_) {

PoseMessage pose_msg;
OdometryMessage odom_msg;
Deserializer deserializer;
Identifiable identifiable;
BoolData data(true);
DynamicLoaderConfig dynloader;
SerializationContext ctx;
MatrixInt m;



std::cout << R"(
 _______________________________________________________
/                                                       \
|  Congratulations, you have completed this homework!   |
\_________              _______________________________/ 
          \_         __/    ___---------__               
            \      _/      /              \_             
             \    /       /                 \            
              |  /       | _    _ \          \           
              | |       / / \  / \ |          \          
              | |       ||   ||   ||           |         
              | |       | \_//\\_/ |           |         
              | |       |_| (||)   |_______|   |         
              | |         |  ||     | _  / /   |         
               \ \        |_________|| \/ /   /          
                \ \_       |_|_|_|_|/|  _/___/           
                 \__>       _ _/_ _ /  |                 
                          .|_|_|_|_|   |                 
                          |           /                  
                          |__________/                   

)" << '\n';  
    
}