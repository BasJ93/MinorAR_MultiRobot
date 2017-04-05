; Auto-generated. Do not edit!


(cl:in-package micros_swarm_framework-srv)


;//! \htmlinclude AppUnload-request.msg.html

(cl:defclass <AppUnload-request> (roslisp-msg-protocol:ros-message)
  ((name
    :reader name
    :initarg :name
    :type cl:string
    :initform "")
   (type
    :reader type
    :initarg :type
    :type cl:string
    :initform ""))
)

(cl:defclass AppUnload-request (<AppUnload-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <AppUnload-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'AppUnload-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name micros_swarm_framework-srv:<AppUnload-request> is deprecated: use micros_swarm_framework-srv:AppUnload-request instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <AppUnload-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader micros_swarm_framework-srv:name-val is deprecated.  Use micros_swarm_framework-srv:name instead.")
  (name m))

(cl:ensure-generic-function 'type-val :lambda-list '(m))
(cl:defmethod type-val ((m <AppUnload-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader micros_swarm_framework-srv:type-val is deprecated.  Use micros_swarm_framework-srv:type instead.")
  (type m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <AppUnload-request>) ostream)
  "Serializes a message object of type '<AppUnload-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'type))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'type))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <AppUnload-request>) istream)
  "Deserializes a message object of type '<AppUnload-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'type) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'type) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<AppUnload-request>)))
  "Returns string type for a service object of type '<AppUnload-request>"
  "micros_swarm_framework/AppUnloadRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'AppUnload-request)))
  "Returns string type for a service object of type 'AppUnload-request"
  "micros_swarm_framework/AppUnloadRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<AppUnload-request>)))
  "Returns md5sum for a message object of type '<AppUnload-request>"
  "9e491318c68b9fbf00509a80adfec2ec")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'AppUnload-request)))
  "Returns md5sum for a message object of type 'AppUnload-request"
  "9e491318c68b9fbf00509a80adfec2ec")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<AppUnload-request>)))
  "Returns full string definition for message of type '<AppUnload-request>"
  (cl:format cl:nil "string name~%string type~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'AppUnload-request)))
  "Returns full string definition for message of type 'AppUnload-request"
  (cl:format cl:nil "string name~%string type~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <AppUnload-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'name))
     4 (cl:length (cl:slot-value msg 'type))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <AppUnload-request>))
  "Converts a ROS message object to a list"
  (cl:list 'AppUnload-request
    (cl:cons ':name (name msg))
    (cl:cons ':type (type msg))
))
;//! \htmlinclude AppUnload-response.msg.html

(cl:defclass <AppUnload-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass AppUnload-response (<AppUnload-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <AppUnload-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'AppUnload-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name micros_swarm_framework-srv:<AppUnload-response> is deprecated: use micros_swarm_framework-srv:AppUnload-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <AppUnload-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader micros_swarm_framework-srv:success-val is deprecated.  Use micros_swarm_framework-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <AppUnload-response>) ostream)
  "Serializes a message object of type '<AppUnload-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <AppUnload-response>) istream)
  "Deserializes a message object of type '<AppUnload-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<AppUnload-response>)))
  "Returns string type for a service object of type '<AppUnload-response>"
  "micros_swarm_framework/AppUnloadResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'AppUnload-response)))
  "Returns string type for a service object of type 'AppUnload-response"
  "micros_swarm_framework/AppUnloadResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<AppUnload-response>)))
  "Returns md5sum for a message object of type '<AppUnload-response>"
  "9e491318c68b9fbf00509a80adfec2ec")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'AppUnload-response)))
  "Returns md5sum for a message object of type 'AppUnload-response"
  "9e491318c68b9fbf00509a80adfec2ec")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<AppUnload-response>)))
  "Returns full string definition for message of type '<AppUnload-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'AppUnload-response)))
  "Returns full string definition for message of type 'AppUnload-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <AppUnload-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <AppUnload-response>))
  "Converts a ROS message object to a list"
  (cl:list 'AppUnload-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'AppUnload)))
  'AppUnload-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'AppUnload)))
  'AppUnload-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'AppUnload)))
  "Returns string type for a service object of type '<AppUnload>"
  "micros_swarm_framework/AppUnload")