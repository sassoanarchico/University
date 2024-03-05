# adds an executable named "many_object_in_stack_example", this is a type of target 
add_executable(many_object_in_stack_example many_object_in_stack_example.cpp)
# specify link dependancies for a target use
target_link_libraries(many_object_in_stack_example core_library) 