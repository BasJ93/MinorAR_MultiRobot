# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from micros_swarm_framework/MSFPPacket.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class MSFPPacket(genpy.Message):
  _md5sum = "a47802d49bd3f71134b8d47283707f92"
  _type = "micros_swarm_framework/MSFPPacket"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """int16 packet_source
int8 packet_version
int8 packet_type
string packet_data
int64 package_check_sum
"""
  __slots__ = ['packet_source','packet_version','packet_type','packet_data','package_check_sum']
  _slot_types = ['int16','int8','int8','string','int64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       packet_source,packet_version,packet_type,packet_data,package_check_sum

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(MSFPPacket, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.packet_source is None:
        self.packet_source = 0
      if self.packet_version is None:
        self.packet_version = 0
      if self.packet_type is None:
        self.packet_type = 0
      if self.packet_data is None:
        self.packet_data = ''
      if self.package_check_sum is None:
        self.package_check_sum = 0
    else:
      self.packet_source = 0
      self.packet_version = 0
      self.packet_type = 0
      self.packet_data = ''
      self.package_check_sum = 0

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_struct_h2b.pack(_x.packet_source, _x.packet_version, _x.packet_type))
      _x = self.packet_data
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      buff.write(_struct_q.pack(self.package_check_sum))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      _x = self
      start = end
      end += 4
      (_x.packet_source, _x.packet_version, _x.packet_type,) = _struct_h2b.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.packet_data = str[start:end].decode('utf-8')
      else:
        self.packet_data = str[start:end]
      start = end
      end += 8
      (self.package_check_sum,) = _struct_q.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_struct_h2b.pack(_x.packet_source, _x.packet_version, _x.packet_type))
      _x = self.packet_data
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      buff.write(_struct_q.pack(self.package_check_sum))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      _x = self
      start = end
      end += 4
      (_x.packet_source, _x.packet_version, _x.packet_type,) = _struct_h2b.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.packet_data = str[start:end].decode('utf-8')
      else:
        self.packet_data = str[start:end]
      start = end
      end += 8
      (self.package_check_sum,) = _struct_q.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_q = struct.Struct("<q")
_struct_h2b = struct.Struct("<h2b")
