# generated from rosidl_generator_py/resource/_idl.py.em
# with input from ssafy_msgs:msg\TurtlebotStatus.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_TurtlebotStatus(type):
    """Metaclass of message 'TurtlebotStatus'."""

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
                'ssafy_msgs.msg.TurtlebotStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__turtlebot_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__turtlebot_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__turtlebot_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__turtlebot_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__turtlebot_status

            from geometry_msgs.msg import Twist
            if Twist.__class__._TYPE_SUPPORT is None:
                Twist.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class TurtlebotStatus(metaclass=Metaclass_TurtlebotStatus):
    """Message class 'TurtlebotStatus'."""

    __slots__ = [
        '_twist',
        '_power_supply_status',
        '_battery_percentage',
        '_can_use_hand',
        '_can_put',
        '_can_lift',
    ]

    _fields_and_field_types = {
        'twist': 'geometry_msgs/Twist',
        'power_supply_status': 'uint8',
        'battery_percentage': 'float',
        'can_use_hand': 'boolean',
        'can_put': 'boolean',
        'can_lift': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Twist'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from geometry_msgs.msg import Twist
        self.twist = kwargs.get('twist', Twist())
        self.power_supply_status = kwargs.get('power_supply_status', int())
        self.battery_percentage = kwargs.get('battery_percentage', float())
        self.can_use_hand = kwargs.get('can_use_hand', bool())
        self.can_put = kwargs.get('can_put', bool())
        self.can_lift = kwargs.get('can_lift', bool())

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
        if self.twist != other.twist:
            return False
        if self.power_supply_status != other.power_supply_status:
            return False
        if self.battery_percentage != other.battery_percentage:
            return False
        if self.can_use_hand != other.can_use_hand:
            return False
        if self.can_put != other.can_put:
            return False
        if self.can_lift != other.can_lift:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def twist(self):
        """Message field 'twist'."""
        return self._twist

    @twist.setter
    def twist(self, value):
        if __debug__:
            from geometry_msgs.msg import Twist
            assert \
                isinstance(value, Twist), \
                "The 'twist' field must be a sub message of type 'Twist'"
        self._twist = value

    @property
    def power_supply_status(self):
        """Message field 'power_supply_status'."""
        return self._power_supply_status

    @power_supply_status.setter
    def power_supply_status(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'power_supply_status' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'power_supply_status' field must be an unsigned integer in [0, 255]"
        self._power_supply_status = value

    @property
    def battery_percentage(self):
        """Message field 'battery_percentage'."""
        return self._battery_percentage

    @battery_percentage.setter
    def battery_percentage(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'battery_percentage' field must be of type 'float'"
        self._battery_percentage = value

    @property
    def can_use_hand(self):
        """Message field 'can_use_hand'."""
        return self._can_use_hand

    @can_use_hand.setter
    def can_use_hand(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'can_use_hand' field must be of type 'bool'"
        self._can_use_hand = value

    @property
    def can_put(self):
        """Message field 'can_put'."""
        return self._can_put

    @can_put.setter
    def can_put(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'can_put' field must be of type 'bool'"
        self._can_put = value

    @property
    def can_lift(self):
        """Message field 'can_lift'."""
        return self._can_lift

    @can_lift.setter
    def can_lift(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'can_lift' field must be of type 'bool'"
        self._can_lift = value
