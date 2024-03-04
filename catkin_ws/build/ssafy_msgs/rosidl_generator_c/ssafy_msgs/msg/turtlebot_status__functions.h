// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ssafy_msgs:msg\TurtlebotStatus.idl
// generated code does not contain a copyright notice

#ifndef SSAFY_MSGS__MSG__TURTLEBOT_STATUS__FUNCTIONS_H_
#define SSAFY_MSGS__MSG__TURTLEBOT_STATUS__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_generator_c/visibility_control.h"
#include "ssafy_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "ssafy_msgs/msg/turtlebot_status__struct.h"

/// Initialize msg/TurtlebotStatus message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * ssafy_msgs__msg__TurtlebotStatus
 * )) before or use
 * ssafy_msgs__msg__TurtlebotStatus__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_ssafy_msgs
bool
ssafy_msgs__msg__TurtlebotStatus__init(ssafy_msgs__msg__TurtlebotStatus * msg);

/// Finalize msg/TurtlebotStatus message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ssafy_msgs
void
ssafy_msgs__msg__TurtlebotStatus__fini(ssafy_msgs__msg__TurtlebotStatus * msg);

/// Create msg/TurtlebotStatus message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * ssafy_msgs__msg__TurtlebotStatus__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ssafy_msgs
ssafy_msgs__msg__TurtlebotStatus *
ssafy_msgs__msg__TurtlebotStatus__create();

/// Destroy msg/TurtlebotStatus message.
/**
 * It calls
 * ssafy_msgs__msg__TurtlebotStatus__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ssafy_msgs
void
ssafy_msgs__msg__TurtlebotStatus__destroy(ssafy_msgs__msg__TurtlebotStatus * msg);


/// Initialize array of msg/TurtlebotStatus messages.
/**
 * It allocates the memory for the number of elements and calls
 * ssafy_msgs__msg__TurtlebotStatus__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_ssafy_msgs
bool
ssafy_msgs__msg__TurtlebotStatus__Sequence__init(ssafy_msgs__msg__TurtlebotStatus__Sequence * array, size_t size);

/// Finalize array of msg/TurtlebotStatus messages.
/**
 * It calls
 * ssafy_msgs__msg__TurtlebotStatus__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ssafy_msgs
void
ssafy_msgs__msg__TurtlebotStatus__Sequence__fini(ssafy_msgs__msg__TurtlebotStatus__Sequence * array);

/// Create array of msg/TurtlebotStatus messages.
/**
 * It allocates the memory for the array and calls
 * ssafy_msgs__msg__TurtlebotStatus__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ssafy_msgs
ssafy_msgs__msg__TurtlebotStatus__Sequence *
ssafy_msgs__msg__TurtlebotStatus__Sequence__create(size_t size);

/// Destroy array of msg/TurtlebotStatus messages.
/**
 * It calls
 * ssafy_msgs__msg__TurtlebotStatus__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ssafy_msgs
void
ssafy_msgs__msg__TurtlebotStatus__Sequence__destroy(ssafy_msgs__msg__TurtlebotStatus__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SSAFY_MSGS__MSG__TURTLEBOT_STATUS__FUNCTIONS_H_
