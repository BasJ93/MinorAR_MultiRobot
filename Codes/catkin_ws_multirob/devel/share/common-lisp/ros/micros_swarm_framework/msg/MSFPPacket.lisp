; Auto-generated. Do not edit!


(cl:in-package micros_swarm_framework-msg)


;//! \htmlinclude MSFPPacket.msg.html

(cl:defclass <MSFPPacket> (roslisp-msg-protocol:ros-message)
  ((packet_source
    :reader packet_source
    :initarg :packet_source
    :type cl:fixnum
    :initform 0)
   (packet_version
    :reader packet_version
    :initarg :packet_version
    :type cl:fixnum
    :initform 0)
   (packet_type
    :reader packet_type
    :initarg :packet_type
    :type cl:fixnum
    :initform 0)
   (packet_data
    :reader packet_data
    :initarg :packet_data
    :type cl:string
    :initform "")
   (package_check_sum
    :reader package_check_sum
    :initarg :package_check_sum
    :type cl:integer
    :initform 0))
)

(cl:defclass MSFPPacket (<MSFPPacket>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MSFPPacket>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MSFPPacket)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name micros_swarm_framework-msg:<MSFPPacket> is deprecated: use micros_swarm_framework-msg:MSFPPacket instead.")))

(cl:ensure-generic-function 'packet_source-val :lambda-list '(m))
(cl:defmethod packet_source-val ((m <MSFPPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader micros_swarm_framework-msg:packet_source-val is deprecated.  Use micros_swarm_framework-msg:packet_source instead.")
  (packet_source m))

(cl:ensure-generic-function 'packet_version-val :lambda-list '(m))
(cl:defmethod packet_version-val ((m <MSFPPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader micros_swarm_framework-msg:packet_version-val is deprecated.  Use micros_swarm_framework-msg:packet_version instead.")
  (packet_version m))

(cl:ensure-generic-function 'packet_type-val :lambda-list '(m))
(cl:defmethod packet_type-val ((m <MSFPPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader micros_swarm_framework-msg:packet_type-val is deprecated.  Use micros_swarm_framework-msg:packet_type instead.")
  (packet_type m))

(cl:ensure-generic-function 'packet_data-val :lambda-list '(m))
(cl:defmethod packet_data-val ((m <MSFPPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader micros_swarm_framework-msg:packet_data-val is deprecated.  Use micros_swarm_framework-msg:packet_data instead.")
  (packet_data m))

(cl:ensure-generic-function 'package_check_sum-val :lambda-list '(m))
(cl:defmethod package_check_sum-val ((m <MSFPPacket>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader micros_swarm_framework-msg:package_check_sum-val is deprecated.  Use micros_swarm_framework-msg:package_check_sum instead.")
  (package_check_sum m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MSFPPacket>) ostream)
  "Serializes a message object of type '<MSFPPacket>"
  (cl:let* ((signed (cl:slot-value msg 'packet_source)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'packet_version)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'packet_type)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'packet_data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'packet_data))
  (cl:let* ((signed (cl:slot-value msg 'package_check_sum)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MSFPPacket>) istream)
  "Deserializes a message object of type '<MSFPPacket>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'packet_source) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'packet_version) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'packet_type) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'packet_data) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'packet_data) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'package_check_sum) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MSFPPacket>)))
  "Returns string type for a message object of type '<MSFPPacket>"
  "micros_swarm_framework/MSFPPacket")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MSFPPacket)))
  "Returns string type for a message object of type 'MSFPPacket"
  "micros_swarm_framework/MSFPPacket")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MSFPPacket>)))
  "Returns md5sum for a message object of type '<MSFPPacket>"
  "a47802d49bd3f71134b8d47283707f92")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MSFPPacket)))
  "Returns md5sum for a message object of type 'MSFPPacket"
  "a47802d49bd3f71134b8d47283707f92")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MSFPPacket>)))
  "Returns full string definition for message of type '<MSFPPacket>"
  (cl:format cl:nil "int16 packet_source~%int8 packet_version~%int8 packet_type~%string packet_data~%int64 package_check_sum~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MSFPPacket)))
  "Returns full string definition for message of type 'MSFPPacket"
  (cl:format cl:nil "int16 packet_source~%int8 packet_version~%int8 packet_type~%string packet_data~%int64 package_check_sum~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MSFPPacket>))
  (cl:+ 0
     2
     1
     1
     4 (cl:length (cl:slot-value msg 'packet_data))
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MSFPPacket>))
  "Converts a ROS message object to a list"
  (cl:list 'MSFPPacket
    (cl:cons ':packet_source (packet_source msg))
    (cl:cons ':packet_version (packet_version msg))
    (cl:cons ':packet_type (packet_type msg))
    (cl:cons ':packet_data (packet_data msg))
    (cl:cons ':package_check_sum (package_check_sum msg))
))
