// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from ssafy_msgs:msg\TurtlebotStatus.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_generator_c/visibility_control.h"
#include "ssafy_msgs/msg/turtlebot_status__struct.h"
#include "ssafy_msgs/msg/turtlebot_status__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool geometry_msgs__msg__twist__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * geometry_msgs__msg__twist__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool ssafy_msgs__msg__turtlebot_status__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[49];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp(
        "ssafy_msgs.msg._turtlebot_status.TurtlebotStatus",
        full_classname_dest, 48) == 0);
  }
  ssafy_msgs__msg__TurtlebotStatus * ros_message = _ros_message;
  {  // twist
    PyObject * field = PyObject_GetAttrString(_pymsg, "twist");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__twist__convert_from_py(field, &ros_message->twist)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // power_supply_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "power_supply_status");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->power_supply_status = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // battery_percentage
    PyObject * field = PyObject_GetAttrString(_pymsg, "battery_percentage");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->battery_percentage = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // can_use_hand
    PyObject * field = PyObject_GetAttrString(_pymsg, "can_use_hand");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->can_use_hand = (Py_True == field);
    Py_DECREF(field);
  }
  {  // can_put
    PyObject * field = PyObject_GetAttrString(_pymsg, "can_put");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->can_put = (Py_True == field);
    Py_DECREF(field);
  }
  {  // can_lift
    PyObject * field = PyObject_GetAttrString(_pymsg, "can_lift");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->can_lift = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * ssafy_msgs__msg__turtlebot_status__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of TurtlebotStatus */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("ssafy_msgs.msg._turtlebot_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "TurtlebotStatus");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  ssafy_msgs__msg__TurtlebotStatus * ros_message = (ssafy_msgs__msg__TurtlebotStatus *)raw_ros_message;
  {  // twist
    PyObject * field = NULL;
    field = geometry_msgs__msg__twist__convert_to_py(&ros_message->twist);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "twist", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // power_supply_status
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->power_supply_status);
    {
      int rc = PyObject_SetAttrString(_pymessage, "power_supply_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // battery_percentage
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->battery_percentage);
    {
      int rc = PyObject_SetAttrString(_pymessage, "battery_percentage", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // can_use_hand
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->can_use_hand ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "can_use_hand", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // can_put
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->can_put ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "can_put", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // can_lift
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->can_lift ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "can_lift", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
