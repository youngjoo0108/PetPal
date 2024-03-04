// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from ssafy_msgs:msg\HandControl.idl
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
#include "ssafy_msgs/msg/hand_control__struct.h"
#include "ssafy_msgs/msg/hand_control__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool ssafy_msgs__msg__hand_control__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[41];
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
        "ssafy_msgs.msg._hand_control.HandControl",
        full_classname_dest, 40) == 0);
  }
  ssafy_msgs__msg__HandControl * ros_message = _ros_message;
  {  // control_mode
    PyObject * field = PyObject_GetAttrString(_pymsg, "control_mode");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->control_mode = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // put_distance
    PyObject * field = PyObject_GetAttrString(_pymsg, "put_distance");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->put_distance = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // put_height
    PyObject * field = PyObject_GetAttrString(_pymsg, "put_height");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->put_height = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * ssafy_msgs__msg__hand_control__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of HandControl */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("ssafy_msgs.msg._hand_control");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "HandControl");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  ssafy_msgs__msg__HandControl * ros_message = (ssafy_msgs__msg__HandControl *)raw_ros_message;
  {  // control_mode
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->control_mode);
    {
      int rc = PyObject_SetAttrString(_pymessage, "control_mode", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // put_distance
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->put_distance);
    {
      int rc = PyObject_SetAttrString(_pymessage, "put_distance", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // put_height
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->put_height);
    {
      int rc = PyObject_SetAttrString(_pymessage, "put_height", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
