# generated from rosidl_generator_py/resource/_idl.py.em
# with input from ssafy_msgs:msg\EnviromentStatus.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_EnviromentStatus(type):
    """Metaclass of message 'EnviromentStatus'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('ssafy_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'ssafy_msgs.msg.EnviromentStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__enviroment_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__enviroment_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__enviroment_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__enviroment_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__enviroment_status

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class EnviromentStatus(metaclass=Metaclass_EnviromentStatus):
    """Message class 'EnviromentStatus'."""

    __slots__ = [
        '_month',
        '_day',
        '_hour',
        '_minute',
        '_temperature',
        '_weather',
    ]

    _fields_and_field_types = {
        'month': 'uint8',
        'day': 'uint8',
        'hour': 'uint8',
        'minute': 'uint8',
        'temperature': 'uint8',
        'weather': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.month = kwargs.get('month', int())
        self.day = kwargs.get('day', int())
        self.hour = kwargs.get('hour', int())
        self.minute = kwargs.get('minute', int())
        self.temperature = kwargs.get('temperature', int())
        self.weather = kwargs.get('weather', str())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.month != other.month:
            return False
        if self.day != other.day:
            return False
        if self.hour != other.hour:
            return False
        if self.minute != other.minute:
            return False
        if self.temperature != other.temperature:
            return False
        if self.weather != other.weather:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def month(self):
        """Message field 'month'."""
        return self._month

    @month.setter
    def month(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'month' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'month' field must be an unsigned integer in [0, 255]"
        self._month = value

    @property
    def day(self):
        """Message field 'day'."""
        return self._day

    @day.setter
    def day(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'day' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'day' field must be an unsigned integer in [0, 255]"
        self._day = value

    @property
    def hour(self):
        """Message field 'hour'."""
        return self._hour

    @hour.setter
    def hour(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'hour' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'hour' field must be an unsigned integer in [0, 255]"
        self._hour = value

    @property
    def minute(self):
        """Message field 'minute'."""
        return self._minute

    @minute.setter
    def minute(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'minute' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'minute' field must be an unsigned integer in [0, 255]"
        self._minute = value

    @property
    def temperature(self):
        """Message field 'temperature'."""
        return self._temperature

    @temperature.setter
    def temperature(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'temperature' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'temperature' field must be an unsigned integer in [0, 255]"
        self._temperature = value

    @property
    def weather(self):
        """Message field 'weather'."""
        return self._weather

    @weather.setter
    def weather(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'weather' field must be of type 'str'"
        self._weather = value
