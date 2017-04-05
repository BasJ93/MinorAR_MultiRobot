; Auto-generated. Do not edit!


(cl:in-package micros_swarm_framework-srv)


;//! \htmlinclude RTPDestroy-request.msg.html

(cl:defclass <RTPDestroy-request> (roslisp-msg-protocol:ros-message)
  ((code
    :reader code
    :initarg :code
    :type cl:fixnum
    :initform 0))
)

(cl:defclass RTPDestroy-request (<RTPDestroy-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RTPDestroy-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RTPDestroy-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name micros_swarm_framework-srv:<RTPDestroy-request> is deprecated: use micros_swarm_framework-srv:RTPDestroy-request instead.")))

(cl:ensure-generic-function 'code-val :lambda-list '(m))
(cl:defmethod code-val ((m <RTPDestroy-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader micros_swarm_framework-srv:code-val is deprecated.  Use micros_swarm_framework-srv:code instead.")
  (code m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RTPDestroy-request>) ostream)
  "Serializes a message object of type '<RTPDestroy-request>"
  (cl:let* ((signed (cl:slot-value msg 'code)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RTPDestroy-request>) istream)
  "Deserializes a message object of type '<RTPDestroy-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'code) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RTPDestroy-request>)))
  "Returns string type for a service object of type '<RTPDestroy-request>"
  "micros_swarm_framework/RTPDestroyRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RTPDestroy-request)))
  "Returns string type for a service object of type 'RTPDestroy-request"
  "micros_swarm_framework/RTPDestroyRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RTPDestroy-request>)))
  "Returns md5sum for a message object of type '<RTPDestroy-request>"
  "36405beac40f6723e71d2520ae768ec2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RTPDestroy-request)))
  "Returns md5sum for a message object of type 'RTPDestroy-request"
  "36405beac40f6723e71d2520ae768ec2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RTPDestroy-request>)))
  "Returns full string definition for message of type '<RTPDestroy-request>"
  (cl:format cl:nil "int8 code~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RTPDestroy-request)))
  "Returns full string definition for message of type 'RTPDestroy-request"
  (cl:format cl:nil "int8 code~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RTPDestroy-request>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RTPDestroy-request>))
  "Converts a ROS message object to a list"
  (cl:list 'RTPDestroy-request
    (cl:cons ':code (code msg))
))
;//! \htmlinclude RTPDestroy-response.msg.html

(cl:defclass <RTPDestroy-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass RTPDestroy-response (<RTPDestroy-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RTPDestroy-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RTPDestroy-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name micros_swarm_framework-srv:<RTPDestroy-response> is deprecated: use micros_swarm_framework-srv:RTPDestroy-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <RTPDestroy-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader micros_swarm_framework-srv:success-val is deprecated.  Use micros_swarm_framework-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RTPDestroy-response>) ostream)
  "Serializes a message object of type '<RTPDestroy-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RTPDestroy-response>) istream)
  "Deserializes a message object of type '<RTPDestroy-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RTPDestroy-response>)))
  "Returns string type for a service object of type '<RTPDestroy-response>"
  "micros_swarm_framework/RTPDestroyResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RTPDestroy-response)))
  "Returns string type for a service object of type 'RTPDestroy-response"
  "micros_swarm_framework/RTPDestroyResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RTPDestroy-response>)))
  "Returns md5sum for a message object of type '<RTPDestroy-response>"
  "36405beac40f6723e71d2520ae768ec2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RTPDestroy-response)))
  "Returns md5sum for a message object of type 'RTPDestroy-response"
  "36405beac40f6723e71d2520ae768ec2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RTPDestroy-response>)))
  "Returns full string definition for message of type '<RTPDestroy-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RTPDestroy-response)))
  "Returns full string definition for message of type 'RTPDestroy-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RTPDestroy-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RTPDestroy-response>))
  "Converts a ROS message object to a list"
  (cl:list 'RTPDestroy-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'RTPDestroy)))
  'RTPDestroy-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'RTPDestroy)))
  'RTPDestroy-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RTPDestroy)))
  "Returns string type for a service object of type '<RTPDestroy>"
  "micros_swarm_framework/RTPDestroy")